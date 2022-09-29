<?php
// Connect
include('config.inc');
include('dbconn.php');

$sql = "SELECT reset FROM `switch` WHERE dev_id='1'";
$result = $pdo->query($sql);

if ($result-> rowCount() > 0) {
  while($row = $result-> fetch(PDO::FETCH_ASSOC)) {
    echo "" . $row["reset"]. "";
  }
} else {
  echo "0 results";
}

?>