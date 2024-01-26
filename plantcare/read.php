<?php

include_once 'database.php';
include_once 'data.php';

// get database connection
$database = new Database();
$db = $database->getConnection();

$data = new Data($db);

$stmt = $data->readAll();
$num = $stmt->rowCount();
$json_data = array();
$i=0;
    while($row = $stmt->fetch(PDO::FETCH_ASSOC)){
        extract($row);
        $json_data[$i++] = array(
            "param" => $param,
            "value" => $value
        );
    } 

    echo json_encode($json_data);

?>
