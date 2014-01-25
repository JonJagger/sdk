<?php

require_once('login_table.inc');

$newPassword = LoginTable::encrypt('password');
$newPassword = addslashes($newPassword);
echo $newPassword;

?>

