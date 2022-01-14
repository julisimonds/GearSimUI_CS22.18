#include "tableModel.h"

tableModel::tableModel(QObject* parent, GearSimDataTable* data) : QAbstractTableModel(parent), tableData(data) {}

int tableModel::rowCount(const QModelIndex& index) const {
	int count = 0;
	if (tableData) {
		count = tableData->getData()[0].size();
	}
	return count;
}

int tableModel::columnCount(const QModelIndex& index) const {
	int count = 0;
	if (tableData) {
		count = tableData->getData().size();

	}
	return count;
}

//TODO: use table's column names, or provide a default given blank string

QVariant tableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
	switch (section) {
	case 0:
		return "ColumnOne";
	case 1:
		return "ColumnTwo";
	default:
		return "Default";
	}
}

QVariant tableModel::data(const QModelIndex& index, int role) const {
	if (role != Qt::DisplayRole && role != Qt::EditRole) return {};
	
  if (index.column() < tableData->getData().size() && index.row() < tableData->getData()[index.column()].size()) {
		return tableData->getData()[index.column()][index.row()];
	} else {
		return {};
	}
}

Qt::ItemFlags tableModel::flags(const QModelIndex& index) const
{
	return (Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
}

bool tableModel::setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) {
	double point = value.value<double>();

	tableData->setPoint(index.column(), index.row(), point);
	
	emit dataChanged(index, index);
	return true;
}

