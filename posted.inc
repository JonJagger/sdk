<?php

function posted($variable)
{
    global $_POST;
    $v = $_POST[$variable];
    return ini_get('magic_quotes_gpc') ? stripslashes($v) : $v;
}

?>
