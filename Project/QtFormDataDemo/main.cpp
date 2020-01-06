#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>

bool requestUploadImages(const QStringList& vsFileList, QString& strResp)
{
	QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
	for (const auto& filePathIter : vsFileList)
	{
		// ����ļ��ֳɶ����
		QHttpPart imagePart;
		QFileInfo filInfo(filePathIter);
		QFile file(filePathIter);
		if (!file.open(QIODevice::ReadOnly))
		{
			continue;
		}

		//��������Լ���Э����Ӷ�Ӧ����
		imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
			QVariant(QString("form-data; name=\"uploadfile\"; filename=\"%1\"").arg(filInfo.fileName()))); 
		// ���� �����Լ���Ҫ��Э����ж���
		imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png")); 

		const auto& data = file.readAll();
		imagePart.setBody(data);// ��body���������ļ�����
		// ���ݳ��Ȳ����Ͽ��ܵ���ʧ��
		imagePart.setHeader(QNetworkRequest::ContentLengthHeader, QVariant(data.size()));
		multiPart->append(imagePart);
	}

	QUrl url("http://www.csu.edu.cn"); // ����url Ҫ�����Լ�ʵ��ʹ�õ�URI
	QNetworkRequest request(url);
	QNetworkAccessManager manager;
	QNetworkReply *reply = manager.post(request, multiPart);

	multiPart->setParent(reply); // ͨ��replyɾ��multiPart����

	QObject::connect(reply, &QNetworkReply::finished, [&reply, &strResp]
	{
		if (reply->error() == QNetworkReply::NoError)
		{
			strResp = reply->readAll();
			qDebug() << "upload file finished";
		}
		else
		{
			strResp = reply->errorString();
			qDebug() << "error string:" << reply->errorString();
		}
	});

	QEventLoop eventLoop;
	QObject::connect(&manager, &QNetworkAccessManager::finished, [&]
	{
		eventLoop.quit();
	});
	eventLoop.exec();

	reply->deleteLater();

	return true;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QString resp;
	requestUploadImages(QStringList(), resp);
	qDebug() << resp;

	return a.exec();
}
