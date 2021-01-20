<?php
date_default_timezone_set('Asia/Jakarta');
$dbhost = "localhost";
$dbuser = "root";
$dbpass = "";
$dbname = "fanselectronics_phpiot";
$url = "http://" . $_SERVER["HTTP_HOST"] . dirname($_SERVER["SCRIPT_NAME"]);
$conn = new mysqli($dbhost, $dbuser, $dbpass, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
