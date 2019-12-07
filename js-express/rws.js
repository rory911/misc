//
// Another simple minded REST example using Node.js with Express routing and JSON to create
// and update a MySQL database of records with a RESTful API (POST, GET, PUSH, PATCH, DELETE).
// Postman is recommended to drive the service, but any RESTful API tool will do, say curl.
//
// Experience with Node.js, Express, JSON, Postman, phpMyAdmin, and MySQL setup and config
// are assumed. Additionally, knowledge of URL query strings is required with Postman. This
// code is very simplistic, there is no auth/security and SQL commands are extremely limited.
// This is just another example of a SQL database using Postman and MySQL/phpMyAdmin/Apache
// from XAMPP, but instead executing with JavaScript under an asynchronous Node runtime.
//
const express = require('express');
const mysql = require('mysql');
const util = require('util');
const path = require('path')
const app = express();
const hostname = 'localhost'
const port = process.env.PORT || 8080

const conn = mysql.createConnection({
	host: 'localhost',
	user: 'root',
	password: '',
	database: 'foo'
});

//
// Connect to the port
//
app.listen(port, () => {
	console.log(`Server running on ${hostname}:${port}`);
});

//
// Connect to the MySQL database
//
conn.connect(function(error) {
	if (error)
		console.log(error)
});

//
// Home Page
//
app.get('/', (req, res) => {
	res.sendFile(path.join(__dirname+'/index.html'));
});

//
// Dump all database records from mysql-records endpoint
//
app.get('/mysql-records', (req, res) => {
	conn.query("SELECT * FROM `records`", (err, rows, fields) => {
		if (err) throw err;
		res.send(rows);
	});
});

//
// From Postman, send GET from mysql-records with <id> in the endpoint
//
app.get('/mysql-records/:id', (req, res) => {
	cmd = util.format("SELECT * FROM `records` WHERE ID=", req.params.id)
	conn.query(cmd, (err, rows, fields) => {
		if (err) throw err;
		res.send(rows);
	});
});

//
// From Postman, send PUT from mysql-records endpoint
//
// Both <title> and <desc> are required for this method.
//
app.put('/mysql-records', (req, res) => {
	len = 0;
	conn.query("SELECT COUNT(*) AS cnt FROM `records`", (err, rows, fields) => {
		if (err) throw err
		len = 1 + rows[0].cnt;
		if (!req.query.title || !req.query.desc) {
			res.send("PUT: requires title and description");
			return;
		}
		cmd = util.format("INSERT INTO `records` VALUES('%s', '%s', '%s')",
		    len, req.query.title, req.query.desc);
		conn.query(cmd, (err, rows, fields) => {
			if (err) throw err;
			res.send(rows);
		});
	});
});

//
// From Postman, send DELETE from mysql-records with <id> in the endpoint
//
// Record <id> will be purged if it exits.
//
app.delete('/mysql-records/:id', (req,res) => {
	cmd = util.format("DELETE FROM `records` WHERE ID=", req.params.id)
	conn.query(cmd, (err, rows, fields) => {
		if (err) throw err;
		if (rows.affectedRows == 0) {
			res.send("Record does not exist")
		} else {
			res.send("Delete complete")
		}
	});
});

//
// From Postman, send PATCH from mysql-records with <id> in the endpoint
//
// Either <title> or <desc> or both are required for this method.
//
app.patch('/mysql-records/:id', (req, res) => {
	title = " "
	desc = " "
	cmd = util.format("UPDATE `records` SET ")
	id = util.format(" WHERE ID='%d'", req.params.id)
	if (!req.query.title && !req.query.desc) {
		res.send("PUT: requires title or description");
		return;
	}
	if (req.query.title) {
		title = util.format("`TITLE`='%s'", req.query.title)
		if (req.query.desc)
			desc = util.format(", `DESC`='%s'", req.query.desc)
	} else if (req.query.desc) {
		desc = util.format("`DESC`='%s'", req.query.desc)
	}
	conn.query(cmd+title+desc+id, (err, rows, fields) => {
		if (err) throw err;
		if (rows.affectedRows == 0) {
			res.send("Record does not exist")
		} else {
			res.send(rows)
		}
	});
});
