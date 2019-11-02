package main

import (
    "fmt"
    "net/http"
    "github.com/gorilla/websocket"
)

const	DEBUG		= false
var	upgrader	= websocket.Upgrader{ReadBufferSize: 1024, WriteBufferSize: 1024}

// HTTP sockets to connect sales to customers
var	Sales		*websocket.Conn
var	Customer	*websocket.Conn


// Representative chat with customer
func fromSales(w http.ResponseWriter, r *http.Request) {
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		fmt.Println(err)
		return
	}
	Sales = conn

	for {
		// Read message from Sales
		msgType, msg, err := conn.ReadMessage()
		if err != nil {
			fmt.Println(err)
			return
		}

		if DEBUG {
			// Print message and RemoteAddr to the console
			fmt.Printf("Sales: %s, addr=%s\n", string(msg), conn.RemoteAddr())
		}

		// Forward message Customer
		if Customer != nil {
			if err = Customer.WriteMessage(msgType, msg);  err != nil {
				fmt.Println(err)
				return
			}
		}
	}
}

// Customer chat with sales representative
func fromCustomer(w http.ResponseWriter, r *http.Request) {
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		fmt.Println(err)
	}
	Customer = conn

	for {
		// Read message from Customer
		msgType, msg, err := conn.ReadMessage()
		if err != nil {
			fmt.Println(err)
			return
		}

		if DEBUG {
			// Print message and RemoteAddr to the console
			fmt.Printf("Customer: %s, addr=%s\n", string(msg), conn.RemoteAddr())
		}

		// Forward message Sales
		if Sales != nil {
			if err = Sales.WriteMessage(msgType, msg);  err != nil {
				fmt.Println(err)
				return
			}
		}
	}
}

// Serve javascript to capture chat dialog for sales representatives
func sales(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "sales.html")
}

// Serve javascript to capture chat dialog for customers
func customer(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "customer.html")
}

//
// Simple minded chat between sales and customers using Gorilla websockets
//
func main() {
	http.HandleFunc("/salesChan", fromSales)
	http.HandleFunc("/sales", sales)
	http.HandleFunc("/customerChan", fromCustomer)
	http.HandleFunc("/customer", customer)

	http.ListenAndServe(":8080", nil)
}
