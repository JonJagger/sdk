<?php
session_start();

require_once('session.inc');
require_once('redirect.inc');

$method = $_SERVER['REQUEST_METHOD'];

if ($method == 'POST') 
{
    session_remember('auth', false);
    redirect("/login.php");
}
else
{
    die("This script only works with POST requests");
}

?>
