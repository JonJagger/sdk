<?php

function session_remember($key, $value)
{
    setcookie($key, $value);
}

function session_retrieve($key)
{
    return $_COOKIE[$key];
}

function is_authenticated()
{
    $auth = session_retrieve('auth');
    return isset($auth);
}

?>
