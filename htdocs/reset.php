<?php
// Connect
include('config.inc');
include('dbconn.php');

// Update data in DB
try {
	$statement = $pdo->prepare("UPDATE Switch SET reset='0' WHERE dev_id=1");
	$statement->execute();
	} catch(PDOException $e) {
         echo '<br />';
	  echo $e->getMessage();
         echo '<br />';
    }
$result = $statement->execute();
if ($result = 1) {
	echo '<br />';
	echo 'Succes';
	echo '<br />';
} else {
	echo '<br />';
	echo 'Failure';
	echo '<br />';
}

// Close DB connection
try {
	$pdo = null;
}

catch(PDOException $e)
{
	echo $e->getMessage();
}

?>