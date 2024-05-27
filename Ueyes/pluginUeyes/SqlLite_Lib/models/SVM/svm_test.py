def main():
    import time #时间
    import jieba # 中文分词
    import codecs # 读取包含中文字符的文件
    import pickle # 特征，模型文件保存和读取
    import pandas as pd # 数据处理
    from sklearn.feature_extraction.text import CountVectorizer # 将文本中的词语转换为词频矩阵
    from sklearn.feature_extraction.text import TfidfTransformer # 用于计算每个词语的TF-IDF值
    import joblib
    import xiangshi as xs
    import itertools

    test_true = list()
    train_file = "../../data/train.txt"
    train_data = pd.read_csv(train_file, sep="\t", header=None, names=["id", "category", "sentence"])

    categories = sorted(list(set(list(train_data['category']))))
    category2tag = dict()
    tag2category = dict()
    for i, category in enumerate(categories):
        category2tag[category] = i
        tag2category[i] = category
        print("\x1b[32m{:>35}\x1b[0m >>>>>>>>>>>>>>>>>>>> \x1b[31m{:<2}\x1b[0m".format(category, i))


    start_time = time.time()
    model = joblib.load('SVM_model.mkl')
    print("training took {}s!".format(time.time() - start_time))

    def predict(sentence):
        words = [word for word in jieba.cut(sentence)]
        sentence1 = ' '.join(words)

        vectorizer = CountVectorizer(decode_error="replace",vocabulary=pickle.load(open("SVM_tfidf_feat.pkl", "rb")))
        sentence2 = vectorizer.transform([sentence1])
        transformer = TfidfTransformer()
        tfidf = transformer.fit_transform(sentence2)
        sentence3 = tfidf.toarray()

        predicts = model.predict(sentence3)
        predict_category = tag2category[predicts[0]]
        return predict_category


    with codecs.open("../../data/test_gold.txt", "r", encoding="utf-8") as f:
        test_true = [line.strip().split("\t")[1] for line in f]
    test_file = "../../data/wen.txt"
    test_data = pd.read_csv(test_file, sep="\t", header=None, names=["id", "sentence"])
    test_pred = list()
    test_sentences = list(test_data["sentence"])
    n = 0
    with codecs.open("SVM_test_predict.txt", "w", encoding="utf-8") as f:
        sentence = []
        for s in test_sentences:
            n += 1
            c = predict(s)
            test_pred.append(c)
            f.write("s{}\t{}\t{}\n".format(n,c,s))
            if c == "Addictive Behavior":
                sentence.append(s)
                print("[text]：\x1b[36m{:>0}\x1b[0m".format(s))
    def get_key(my_dict, value):
        for key, val in my_dict.items():
            if val == value:
                return key
        return None
    def calTfIdf(sentences):
        # 使用jieba进行中文分词，并以空格隔开。
        preprocess_setences = []
        shopping_list = []
        for sentence in sentences:
            words = [word for word in jieba.cut(sentence)]
            preprocess_setences.append(' '.join(words))

        # 根据词频选择词量，确定词向量维度
        vectorizer = CountVectorizer(max_features=500, binary=True)   # 将文本中的词语转换为词频矩阵
        word_counts = vectorizer.fit_transform(preprocess_setences) # 计算每个词语出现的次数
        vectorizer.vocabulary_ = {k: v for k, v in sorted(vectorizer.vocabulary_.items(), key=lambda item: item[1])}
        # 计算TF-IDF
        transformer = TfidfTransformer()
        tfidf = transformer.fit_transform(word_counts)
        return list(tfidf.toarray()), vectorizer.vocabulary_
    tfidf_matrix,dict = calTfIdf(sentence)

    avg_tfidf = []
    need_col = []
    for col_index in range(len(list(dict))):
        col_sum = 0
        non_zero_count = 0
        max_num = 0
        max_col = 0
        for i,row in enumerate(tfidf_matrix):
            if row[col_index] >= max_num:
                max_num = row[col_index]
                max_col = i
        avg_tfidf.append([max_num,max_col])
        need_col.append(max_col)
    # print(avg_tfidf,list(set(need_col)))
    for i in list(set(need_col)):
        print(sentence[i])
        # 输出第二列的平均值
    #%%
    #测试通过相似度tf值来降维
    #%%

    similarity_list = [0 for i in range(len(sentence))]
    xs.weight = "TFIDF" # 将加权方式设置为TFIDF
    xs.construct(sentence) # 输入TFIDF文本，相同的文本只需调用这个函数一次
    for i, j in itertools.combinations(range(len(sentence)), 2):
        similarity = xs.cossim(sentence[i],sentence[j])
        similarity_list[i] += similarity
        similarity_list[j] += similarity

    # print(similarity_list)

        # similarities.append(similarity)
    data = pd.DataFrame(similarity_list,index = list(sentence),columns=["value"])
    data = data.drop_duplicates()
    data = data.sort_values(by='value',ascending=True)
    return data[0:10]