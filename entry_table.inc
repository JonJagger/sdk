<?php

require_once('database.inc');
require_once('xslt_annotation.inc');

class EntryTable
{
    static function create_table()
    {
$sql = <<< SQL
        CREATE TABLE entries
        (
            title varchar(512) not null default '',           
            xml_content mediumtext not null,
            ts timestamp default current_timestamp on update current_timestamp,
            primary key (title)
        );
SQL;

        $lid = Database::connect();
        $r = Database::query($sql, $lid);
        Database::close($lid);
    }

    #-------------------------------------------

    static function remove($title)
    {
        $title = addslashes($title);

$sql = <<< SQL
        DELETE FROM entries WHERE title='$title';
SQL;

        $lid = Database::connect();
        Database::query($sql, $lid);
        Database::close($lid);   
    }

    #--------------------------------------------

    static function rename($title, $new_title)
    {
        $xml = EntryTable::get($title);

        #change title attribute in top level <entry>
        $new_xml = xml_rename($xml, $new_title);
        $new_xml = addslashes($new_xml);

        $title = addslashes($title);
        $new_title = addslashes($new_title);
        $ts = EntryTable::get_ts($title);

$sql = <<< SQL
        UPDATE entries  
           SET title='$new_title' , xml_content='$new_xml' 
           WHERE title='$title' and ts='$ts';
SQL;

        $lid = Database::connect();
        Database::query($sql, $lid);
        Database::close($lid);        
    }

    #--------------------------------------------

    static function insert($title, $xml_content)
    {
        $title = addslashes($title);
        $xml_content = addslashes($xml_content);

$sql = <<< SQL
        INSERT INTO entries VALUES ('$title', '$xml_content', null);
SQL;

        $lid = Database::connect();
        Database::query($sql, $lid);
        $result = mysql_affected_rows();
        Database::close($lid);
        return $result;
    }

    #--------------------------------------------

    static function change($title, $xml_content, $ts)
    {
        $current = EntryTable::get($title);
        if ($current == $xml_content)
        {
            return 1;
        }

        $title = addslashes($title);
        $xml_content = addslashes($xml_content);

$sql = <<< SQL
        UPDATE entries  
           SET xml_content='$xml_content' 
           WHERE title = '$title' and ts = '$ts';
SQL;

        $lid = Database::connect();
        Database::query($sql, $lid);
        $result = mysql_affected_rows();
        Database::close($lid);        
        return $result;
    }

    #--------------------------------------------

    static function get($title)
    {
        $title = addslashes($title);

$sql = <<< SQL
        SELECT xml_content FROM entries WHERE title = '$title'
SQL;

        $lid = Database::connect();
        $result = Database::query($sql, $lid);
        $row = mysql_fetch_row($result);
        Database::close($lid);

        return $row[0];
    }

    #--------------------------------------------

    static function get_ts($title)
    {
        $title = addslashes($title);

$sql = <<< SQL
        SELECT ts FROM entries WHERE title = '$title'
SQL;

        $lid = Database::connect();
        $result = Database::query($sql, $lid);
        $row = mysql_fetch_row($result);
        Database::close($lid);

        return $row[0];
    }

    #--------------------------------------------

    static function get_just_titles()
    {
$sql = <<< SQL
        SELECT title FROM entries
SQL;
       $lid = Database::connect();
       $rows = Database::query($sql, $lid);
       while ($row = mysql_fetch_array($rows))
       {
          $res[] = $row;   
       }
       Database::close($lid);

       return $res;
    }

    #--------------------------------------------

    static function get_all_titles()
    {
$sql = <<< SQL
        SELECT title,xml_content,ts FROM entries
SQL;
       $lid = Database::connect();
       $rows = Database::query($sql, $lid);
       while ($row = mysql_fetch_array($rows))
       {
          $res[] = $row;   
       }
       Database::close($lid);

       return $res;
    }
}

?>
