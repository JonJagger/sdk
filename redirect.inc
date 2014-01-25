<?php

require_once('root_url.inc');

function redirect($to)
{
    $url = root_url() . $to;
    header("Location: http://$url");
    #exit;
}

?>