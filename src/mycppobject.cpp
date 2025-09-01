#include <QObject>
#include <QDebug>

class MyCppObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString myText READ myText WRITE setMyText NOTIFY myTextChanged)

public:
    explicit MyCppObject(QObject *parent = nullptr) : QObject(parent), m_myText("Initial Text") {}

    QString myText() const { return m_myText; }
    void setMyText(const QString &text) {
        if (m_myText != text) {
            m_myText = text;
            emit myTextChanged();
        }
    }

signals:
    void myTextChanged();

private:
    QString m_myText;
};
