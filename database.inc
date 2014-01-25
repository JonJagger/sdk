<?php

$name = 'sdk_db';

class Database
{
    static function create()
    {
        # NB: don't select_db on a create

        global $name;
        $sql = "create database $name";
        $lid = Database::connect();

        $q = mysql_query($sql, $lid);
        if (!$q) {
            die('mysql:Error during create $name: ' . mysql_error());
        }
    }

    static function drop()
    {
        # NB: don't select_db on a create

        global $name;
        $sql = "drop database $name";
        $lid = Database::connect();

        $q = mysql_query($sql, $lid);
        if (!$q) {
            echo "Could not drop $name: " . mysql_error() . "\n";
        }
    }

    static function connect()
    {
        $lid = mysql_connect('localhost', 'root', 'jubilee42');
        if (!$lid) {
            die('mysql:Error during connect: ' . mysql_error());
        } else {
            return $lid;
        } 
    }

    function query($sql, $lid)
    {
        global $name;

        $s = mysql_select_db($name, $lid);
        if (!$s) {
            die("mysql:Error selecting database $name: " . mysql_error());
        }
        $q = mysql_query($sql, $lid);
        if (!$q) {
            die('mysql:Error during query: ' . mysql_error());
        }
        return $q;
    }

    function close($lid)
    {
        $r = mysql_close($lid);
        if (!$r) {
            die('mysql:Error during close: ' . mysql_error());
        }
    }
}

?>
