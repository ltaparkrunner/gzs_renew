import QtQuick 2.0
import QtQuick.Controls 1.5

Rectangle { color: "ivory"
                TableView {
                    anchors.fill: parent
                    clip: true

                    TableViewColumn {
                        role: "customer"
                        title: "Customer"
                    }

                    TableViewColumn {
                        role: "address"
                        title: "Address"
                    }

                    TableViewColumn {
                        role: "mobile"
                        title: "Mobile"
                    }

                    model: ListModel {

                        ListElement {
                            customer: "h1"
                            address: "down1"
                            mobile: "345561"
                        }
                        ListElement {
                            customer: "h2"
                            address: "down2"
                            mobile: "345562"
                        }
                        ListElement {
                            customer: "h3"
                            address: "down3"
                            mobile: "345563"
                        }
                    }
                }
            }
