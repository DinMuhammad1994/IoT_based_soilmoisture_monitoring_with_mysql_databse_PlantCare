<?php
class Data{
 
    // database connection and table name
    private $conn;
    private $table_name = "data";
 
    // object properties
    public $param;
    public $value;

    public function __construct($db){
        $this->conn = $db;
    }
 

    // update product
    public function update($param,$value){
 
        //write query
        $query = "UPDATE
                    ".$this->table_name."
                SET
                    value=$value
                WHERE param=\"$param\";
                    ";
        $stmt = $this->conn->prepare($query);
        
        if($stmt->execute()){
            return true;
        }else{
            return false;

        }
 
    }

    public function read($param){
 
        $query = "SELECT
                    *
                FROM
                    " . $this->table_name . "
                WHERE param='$param';
                ";
     
        $stmt = $this->conn->prepare( $query );
        $stmt->execute();
     
        return $stmt;
    }

    public function readAll(){
 
        $query = "SELECT
                    param, value
                FROM
                    " . $this->table_name;
     
        $stmt = $this->conn->prepare( $query );
        $stmt->execute();
     
        return $stmt;
    }

    // resgister email
    public function register($name,$email,$gender,$location){
 
        //write query
        $query = "INSERT INTO
                    emails
                SET
                    name='$name', email='$email', gender='$gender', location='$location'";
 
        $stmt = $this->conn->prepare($query);
 
        if($stmt->execute()){
            return true;
        }else{
            return false;
        }
 
    }

    public function getEmails(){
        $query = "SELECT * FROM emails;";
          
        $stmt = $this->conn->prepare( $query );
        $stmt->execute();
     
        return $stmt;
    }

    public function verifyLogin($username,$password){
        $query = "SELECT * FROM admins WHERE username='$username' AND password='$password'";
          
        $stmt = $this->conn->prepare( $query );
        $stmt->execute();
            $rows = $stmt->rowCount();
        if($rows>0)
            return true;
        else
            return false;
    }
}
