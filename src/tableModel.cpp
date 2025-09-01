#include <QObject>
#include <QAbstractTableModel>
#include <qqml.h>

class TableModel2 : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    int rowCount(const QModelIndex & = QModelIndex()) const override
    { return 1; }

    int columnCount(const QModelIndex & = QModelIndex()) const override
    { return 8; }

    QVariant data(const QModelIndex &index, int role) const override
    {
        switch (role) {
            case Qt::DisplayRole:
                return QString("%1, %2").arg(index.column()).arg(index.row());
            default: break;
        }
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override
    {
        return {{Qt::DisplayRole, "display"}};
    }
};
