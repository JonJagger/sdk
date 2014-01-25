<?php
session_start();

require_once('make_view_page.inc');
require_once('redirect.inc');
require_once('session.inc');

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

$title = $_GET['title'];
if ($title == "")
{
   # TODO: 
}

$method = $_SERVER['REQUEST_METHOD'];
if ($method == 'GET') 
{
    if (is_authenticated())
        echo make_view_page($title);
    else
        redirect("/login.php?title=$title");
}
else if ($method == 'POST') 
{
    if ($_POST['edit'])
        redirect("/edit.php?title=$title");
    else
        die('BUG: unexpected form POST submission');
} 
else 
{
    die('This script only works with GET and POST requests');
}

?>
