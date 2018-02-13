#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include <Table.h>

class FieldsListModel : public QAbstractItemModel
{
public:
	FieldsListModel(Table *table)
	    : table(table) {}

	int rowCount(const QModelIndex &parent) const override
	{
		return table->get_numfields();
	}

	int columnCount(const QModelIndex &parent) const override
	{
		return 6;
	}

	QModelIndex index(int row, int column, const QModelIndex &parent) const override
	{
		return QAbstractItemModel::createIndex(row, column);
	}

	QModelIndex parent(const QModelIndex &child) const override
	{
		return QModelIndex();
	}


	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
	{
		if (!index.isValid()) {
			return QVariant();
		}
		if (role == Qt::DisplayRole) {
			Field *f = table->getfield(index.row());
			switch (index.column()) {
			case 0:
				return QString::fromStdString(
				                               static_cast<std::string>(f->getname()));

			case 1:
				return QString::fromStdString(static_cast<std::string>(f->get_presentation_type()));
			case 2:
				return QVariant::fromValue(f->getlength());
			case 3:
				return QVariant::fromValue(f->getprecision());
			case 4:
				return f->getnull_exists() ? QString("NULL") : QString("NOT NULL");
			case 5:
				return f->getcase_sensitive() ? QString("CS") : QString("CI");
			} // switch
		}

		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
			switch (section) {
			case 0:
				return tr("Name");
			case 1:
				return tr("Type");
			case 2:
				return tr("Length");
			case 3:
				return tr("Precision");
			case 4:
				return tr("NULL");
			case 5:
				return tr("Case Sensitivity");
			}
		}
		return QVariant();
	}

	Table *table;
};

namespace Ui {
class TableWindow;
}

class TableWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit TableWindow(QWidget *parent, Table *table);
	~TableWindow();

private:
	Table *table;
	Ui::TableWindow *ui;
};

#endif // TABLEWINDOW_H
