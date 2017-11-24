# batch_face_detect
make the batch_face_detect from ID_card by opencv
通过opencv自带的基于haar特征的函数对身份证图片进行批量检测人脸
注意：opencv自带的基于haar特征检测人脸的函数有好几个，没有全部比较，但发现faceCascade.detectMultiScale（）函数效果最好，其中：900张身份证图片中，检测结果分为三种：（1）16张检测不到人脸；（2）2张检测到多个人脸；（3）准确检测到一个人脸；  不存在检测到一个目标，且该目标不是人脸的情况。
ps:突然发现自己有了做人脸方面的一个小数据集了，哈哈~
