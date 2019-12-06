//
// Simple RWS Golang using the standard net/http mux and JSON to create and update a
// MySQL database of records with a RESTful API (POST, GET, PUSH, PATCH, DELETE). Postman
// is recommended to drive the RWS, however, any RESTful API tool will do, say curl.
//
// Experience with the Golang environment, JSON, Postman, phpMyAdmin, and MySQL setup and
// configuration are assumed. Additionally, knowledge of URL query strings is required with
// Postman.  This code is very simple minded, there is no auth/security and SQL commands are
// extremely limited in this example.  This is more about being an example of a SQL database
// using Postman and MySQL/phpMyAdmin/Apache from XAMPP (MariaDB default).
//
package main

import (
	"fmt"
	"log"
	"database/sql"
	_ "github.com/go-sql-driver/mysql"
	"net/http"
	"io/ioutil"
	"encoding/json"
	"strconv"
)

type Record struct {
	ID	string `json:"id"`
	Title	string `json:"title"`
	Desc	string `json:"desc"`
}

type Modify struct {
	id	string
	title	string
	desc	string
}

var table *sql.DB

func homePage(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "<html><body><font size='5'><center>")
	fmt.Fprintf(w, "Process SQL records with standard net/http services")
	fmt.Fprintf(w, "</center><br><font size='4'>This simple Golang program uses the ")
	fmt.Fprintf(w, "following JSON records to feed the SQL database:<br>");
	fmt.Fprintf(w, "<pre>\t<b>ID:</b> <i>string</i><br>")
	fmt.Fprintf(w, "\t<b>Title:</b> <i>string</i><br>\t<b>Desc:</b> <i>string</i></pre>")
	fmt.Fprintf(w, "Navigate to <a href='MySQL-records'>mysql-records</a> and use the ")
	fmt.Fprintf(w, "RESTful interface for building and modifying the SQL database. ")
	fmt.Fprintf(w, "&nbsp; Postman and phpMyAdmin are recommended for driving the ")
	fmt.Fprintf(w, "interface with POST, GET, PUT, PATCH, and DELETE.&nbsp; ")
	fmt.Fprintf(w, "Experience with URL query strings is required with Postman. &nbsp; ")
	fmt.Fprintf(w, "Refresh MySQL-records after each Postman method finishs. &nbsp ")
	fmt.Fprintf(w, "Use the GET method with Postman, or send SQL commands from ")
	fmt.Fprintf(w, "pdpMyAdmin to display the SQL database.</font></body></html>")
}

//
// From Postman, send GET from mysql-records to dump the database
//
func readAllRecords(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")

	// Build the SQL command to dump the database table
	results, err := table.Query("SELECT * FROM `records`")
	if err != nil {
		log.Fatal(err)
	}

	// Build the JSON output in order to display the table
	var numRecords int
	_ = table.QueryRow("SELECT COUNT(*) FROM `records`").Scan(&numRecords)
	i, rec := 0, make([]Record, numRecords)
	for results.Next() {
		err = results.Scan(&rec[i].ID, &rec[i].Title, &rec[i].Desc)
		if err != nil {
			log.Fatal(err.Error())
		}
		i++
	}

	// Dump the entire MySQL table
	json.NewEncoder(w).Encode(&rec)
}

//
// From Postman, send POST from mysql-records with JSON fields to add a record
//
func createRecord(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")

	// Fetch the fields, aka table columns, from the request
	reqBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		json.NewEncoder(w).Encode("createRecord: failed to read parameters")
		return
	}
	var rec Record
	json.Unmarshal(reqBody, &rec)
	if len(rec.Title) < 1 || len(rec.Desc) < 1 {
		json.NewEncoder(w).Encode("createRecord: title and description are required")
		return
	}
	if len(rec.ID) < 1 {
		var numRecords int
		_ = table.QueryRow("SELECT COUNT(*) FROM `records`").Scan(&numRecords)
		rec.ID = strconv.Itoa(numRecords + 1)
	}

	// Build and send the SQL command to create the database record
	cmd := fmt.Sprintf("INSERT INTO `records` VALUES('%s', '%s', '%s')",
	    rec.ID, rec.Title, rec.Desc)
	_, err = table.Query(cmd)
	if err != nil {
		json.NewEncoder(w).Encode("createRecord: INSERT failed")
		return
	}

	// Display the record that was created
	json.NewEncoder(w).Encode(rec)
}

//
// From Postman, send GET from mysql-records with <id> in the URL query string:
//
//	/mysql-records/query?id=<id> where <id> is 1, 2, 3, etc.
//
func readRecord(w http.ResponseWriter, r *http.Request, id string) {
	w.Header().Set("Content-Type", "application/json")


	// Build and send the SQL command to read the database for ID=id
	cmd := fmt.Sprintf("SELECT * FROM `records` WHERE ID='%s'", id)
	result, err := table.Query(cmd)
	if err != nil {
		json.NewEncoder(w).Encode("readRecord: SELECT failed")
		return
	}
	var rec Record
	result.Next()
	err = result.Scan(&rec.ID, &rec.Title, &rec.Desc)
	if err != nil {
		json.NewEncoder(w).Encode("readRecord: Scan failed")
		return
	}

	// Display the requested record
	json.NewEncoder(w).Encode(rec)
}

//
// From Postman, send PUT from mysql-records with fields in the URL query string:
//
//	/mysql-records/query?id=<id>&title=<title>&desc=<desc>
//
// both <title> and <desc> are require for the PUT method.
//
func writeRecord(w http.ResponseWriter, r *http.Request, mod Modify) {
	w.Header().Set("Content-Type", "application/json")

	// Need both title and description
	if len(mod.title) < 1 || len(mod.desc) < 1 { 
		json.NewEncoder(w).Encode("writeRecord: must specify title and descption")
		return
	}

	// Build and send the SQL command to overwrite the record for ID=id
	cmd := fmt.Sprintf("UPDATE `records` SET `TITLE`='%s', `DESC`='%s' WHERE ID='%s'",
	    mod.title, mod.desc, mod.id)
	_, err := table.Query(cmd)
	if err != nil {
		json.NewEncoder(w).Encode("writeRecord: UPDATE(PUT) failed")
		return
	}

	// Display the overwritten record
	readRecord(w, r, mod.id)

}

//
// From Postman, send PATCH from mysql-records with fields in the URL query string:
//
//	/mysql-records/query?id=<id>&title=<title>&desc=<desc>
//
// either <title> and/or <desc> are require for the PATCH method.
//
func updateRecord(w http.ResponseWriter, r *http.Request, mod Modify) {
	w.Header().Set("Content-Type", "application/json")

	// Build the SQL command in order to update the database
	cmd := fmt.Sprintf("UPDATE `records` SET ")
	if len(mod.title) > 0 {
		cmd = cmd + fmt.Sprintf("`TITLE`='%s'", mod.title)
		if len(mod.desc) > 0 {
			cmd = cmd + fmt.Sprintf(", `DESC`='%s' ", mod.desc)
		}
	} else if len(mod.desc) > 0 {
		cmd = cmd + fmt.Sprintf("`DESC`='%s' ", mod.desc)
	} else {
		json.NewEncoder(w).Encode("updateRecord: must specify title or descption")
		return
	}
	cmd = cmd + fmt.Sprintf("WHERE ID='%s'", mod.id)

	// Send the SQL command to the MySQL server
	_, err := table.Query(cmd)
	if err != nil {
		json.NewEncoder(w).Encode("updateRecord: UPDATE(PATCH) failed")
		return
	}

	// Display the updated record
	readRecord(w, r, mod.id)
}

//
// From Postman, send DELETE from mysql-records with <id> in the URL query string:
//
//	/mysql-records/query?id=<id> where <id> is 1, 2, 3, etc.
//
func deleteRecord(w http.ResponseWriter, r *http.Request, id string) {
	w.Header().Set("Content-Type", "application/json")

	// Build and send the SQL command to delete the record ID=id
	cmd := fmt.Sprintf("DELETE FROM `records` WHERE ID='%s'", id)
	_, err := table.Query(cmd)
	if err != nil {
		json.NewEncoder(w).Encode("deleteRecord: DELETE failed")
		return
	}

	// Indicate success
	json.NewEncoder(w).Encode("DELETE completed")
}

//
// Wrapper because net/http lacks .Methods like Gorilla MUX
//
func mysqlRec(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	// Choose response based on the request
	switch r.Method {
	case "GET":
		readAllRecords(w, r)
	case "POST":
		createRecord(w, r)
	default:
		json.NewEncoder(w).Encode(fmt.Sprintf("Invalid Method: %s", r.Method))
	}
}

//
// Wrapper because net/http lacks .Methods like Gorilla MUX and requires query strings
//
func mysqlRecID(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")

	// Parse each field from the query string
	id, ok := r.URL.Query()["id"]
	title, _ := r.URL.Query()["title"]
	desc, _ := r.URL.Query()["desc"]
	if !ok || len(id[0]) < 1 {
		json.NewEncoder(w).Encode("URL: query is invalid or missing")
		return
	}
	var mod Modify
	mod.id = id[0]
	if title != nil {
		mod.title = title[0]
	}
	if desc != nil {
		mod.desc = desc[0]
	}

	// Choose response based on the request
	switch r.Method {
	case "GET":
		readRecord(w, r, id[0])
	case "PUT":
		writeRecord(w, r, mod)
	case "PATCH":
		updateRecord(w, r, mod)
	case "DELETE":
		deleteRecord(w, r, id[0])
	default:
		json.NewEncoder(w).Encode(fmt.Sprintf("Invalid Method: %s", r.Method))
	}
}

//
// Build and modify a simple MySQL database with basic net/http services
//
func main() {
	db, err := sql.Open("mysql", "root@tcp(127.0.0.1:3306)/foo")
	if err != nil {
		log.Fatal(err.Error())
	}
	table = db

	router := http.NewServeMux()
	router.HandleFunc("/", homePage)		       // HTML directions
        router.HandleFunc("/mysql-records", mysqlRec)
        router.HandleFunc("/mysql-records/query", mysqlRecID)
        http.ListenAndServe(":8080", router)

	defer db.Close()
}
