// Copyright 2019 Rory Foster
//
// Simple RWS Golang using Gorilla MUX and JSON to create and update a database
// of JSON records with a RESTful API (POST, GET, PUSH, PATCH, DELETE). Postman
// is recommended to drive the RWS, but any RESTful API tool will do.
//
// Experience with the Golang environment, JSON, Gorilla MUX, and Postman setup
// and configuration are tacitly assumed. Furthermore, knowledge of how to use
// a RESTful API tool, such as Postman, is required
//

package main

import (
	"fmt"
	"github.com/gorilla/mux"
	"net/http"
	"io/ioutil"
	"encoding/json"
	"strconv"
)

// Simple JSON record
type Record struct {
	ID	string `json:"id"`
	Title	string `json:"title"`
	Desc	string `json:"desc"`
}

var records []Record

//
// HTML Home Page with an explanation and hyperlink to the RESTfile API
//
func homePage(w http.ResponseWriter, r *http.Request) {
        fmt.Fprintf(w, "<html><body><font size='5'><center>")
        fmt.Fprintf(w, "Process JavaScript Object Notation (JSON) Records with Gorilla MUX")
        fmt.Fprintf(w, "</center><br><font size='4'>This simple Golang program uses the ")
	fmt.Fprintf(w, "following JSON records:<br><pre>\t<b>ID:</b> <i>string</i><br>")
        fmt.Fprintf(w, "\t<b>Title:</b> <i>string</i><br>\t<b>Desc:</b> <i>string</i></pre>")
        fmt.Fprintf(w, "Navigate to <a href='json-records'>json-records</a> and use the ")
	fmt.Fprintf(w, "RESTful interface for building and modifying the JSON records ")
	fmt.Fprintf(w, "database.&nbsp; Postman is recommended for driving the interface ")
	fmt.Fprintf(w, "with POST, GET, PUT, PATCH, and DELETE.&nbsp; Refresh json-records ")
	fmt.Fprintf(w, "after each Postman method finishs, or use the GET method in order ")
	fmt.Fprintf(w, "to view the current state of the database.</font></body></html>")
}

//
// From Postman, send GET from json-records to dump the database
//
func readAllRecords(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(records)
}

//
// From Postman, send POST (with title and desc only) to append to the database
//
func createRecord(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	reqBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Fprintf(w, "Please p;&nbsp;3 nter title and description")
	}
	var rec Record
	json.Unmarshal(reqBody, &rec)
	rec.ID = strconv.Itoa(len(records) + 1)
	records = append(records, rec)
	json.NewEncoder(w).Encode(&rec)
}

//
// From Postman, send GET (id, title, desc are ignored) from json-records/<id>
// to fetch one record specified by <id>
//
func readRecord(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	params := mux.Vars(r)
	for _, rec := range records {
		if rec.ID == params["id"] {
			json.NewEncoder(w).Encode(rec)
			return
		}
	}
	json.NewEncoder(w).Encode(&Record{})
}

//
// From Postman, send POST (id is ignored) from json-records/<id>
// to overwrite the record specified by <id>
//
func writeRecord(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	params := mux.Vars(r)
	for i, rec := range records {
		if rec.ID == params["id"] {
			reqBody, err := ioutil.ReadAll(r.Body)
			if err != nil {
				fmt.Fprintf(w, "Please enter title and description")
			}

			json.Unmarshal(reqBody, &rec)
			records[i].Title = rec.Title
			records[i].Desc = rec.Desc
			json.NewEncoder(w).Encode(&rec)
			return
		}
	}
	json.NewEncoder(w).Encode(records)
}

//
// From Postman, send PATCH (id is ignored) from json-recors/<id>
// to modify fields of the record specified by <id>
//
func updateRecord(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	params := mux.Vars(r)
	for i, rec := range records {
		if rec.ID == params["id"] {
			reqBody, err := ioutil.ReadAll(r.Body)
			if err != nil {
				fmt.Fprintf(w, "Please enter title and/or description")
			}
			json.Unmarshal(reqBody, &rec)
			if (len(rec.Title) > 0) {
				records[i].Title = rec.Title
			}
			if (len(rec.Desc) > 0) {
				records[i].Desc = rec.Desc
			}
			json.NewEncoder(w).Encode(&rec)
			return
		}
	}
	json.NewEncoder(w).Encode(records)
}

//
// From Postman, send DELETE (id is ignored) from json-records/<id>
// to purge the record specified by <id>
//
func deleteRecord(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	params := mux.Vars(r)
	for index, item := range records {
		if item.ID == params["id"] {
			records = append(records[:index], records[index+1:]...)
			break
		}
	}
	json.NewEncoder(w).Encode(records)
}

//
// Using a Gorilla MUX router, build and modify a very simple JSON database
//
func main() {
	// Simple-minded database init with one record
	records = append(records, Record{ID: "1", Title: "First record",
		Desc: "Initial json record"})

	router := mux.NewRouter()
	router.HandleFunc("/", homePage)	// provide some HTML directions
	router.HandleFunc("/json-records", readAllRecords).Methods("GET")
	router.HandleFunc("/json-records", createRecord).Methods("POST")
	router.HandleFunc("/json-records/{id}", readRecord).Methods("GET")
	router.HandleFunc("/json-records/{id}", writeRecord).Methods("PUT")
	router.HandleFunc("/json-records/{id}", updateRecord).Methods("PATCH")
	router.HandleFunc("/json-records/{id}", deleteRecord).Methods("DELETE")
	http.ListenAndServe(":8080", router)
}
