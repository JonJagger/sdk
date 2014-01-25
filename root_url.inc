<?php

function root_url()
{
    global $_SERVER;
    $host = $_SERVER['SERVER_NAME'];
    return $host ;
}

?>
