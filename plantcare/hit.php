<?php
include_once 'database.php';
include_once 'data.php';



if(!empty($_GET)){
    // get database connection
    $database = new Database();
    $db = $database->getConnection();

    $data = new Data($db);

    $parameter = "";
    $value = 0;
    if(isset($_GET["t"])){
        $parameter = "T";
        $value = $_GET["t"];
        $data->param = $parameter;
        $data->value = $value;

        if ($data->update($parameter,$value))    echo "<div>$parameter $value updated!</div>";
    }
    if(isset($_GET["h"])){
        $parameter = "H";
        $value = $_GET["h"];
        $data->param = $parameter;
        $data->value = $value;

        if ($data->update($parameter,$value))    echo "<div>$parameter $value updated!</div>";
    }
    if(isset($_GET["m1"])){
        $parameter = "M1";
        $value = $_GET["m1"];
        $data->param = $parameter;
        $data->value = $value;

        if ($data->update($parameter,$value))    echo "<div>$parameter $value updated!</div>";
	}
    if(isset($_GET["m2"])){
        $parameter = "M2";
        $value = $_GET["m2"];
        $data->param = $parameter;
        $data->value = $value;

        if ($data->update($parameter,$value))    echo "<div>$parameter $value updated!</div>";
    }
		
   
    
 

   

}


?>