<?php

require_once('database.inc');

class LoginTable
{
    static function create_table()
    {
$sql = <<< SQL
        CREATE TABLE login
        (
            username char(32) not null default '',
            password char(32) not null default '',
            primary key (username)
        );
SQL;

        $lid = Database::connect();
        $r = Database::query($sql, $lid);
        Database::close($lid);
    }

    #-------------------------------------------

    static function add($username, $password)
    {
        $username = addslashes($username);
        $password = LoginTable::encrypt($password);
        $password = addslashes($password);

$sql = <<< SQL
        INSERT INTO login VALUES ('$username', '$password');
SQL;

        $lid = Database::connect();
        $r = Database::query($sql, $lid);
        Database::close($lid);
    }

    #-------------------------------------------
 
    static function change_password($username, $newPassword)
    {
        $username = addslashes($username);
        $newPassword = LoginTable::encrypt($newPassword);
        $newPassword = addslashes($newPassword);

$sql = <<< SQL
        UPDATE login  
           SET password='$newPassword'
           WHERE username='$username';
SQL;

        $lid = Database::connect();
        $r = Database::query($sql, $lid);
        Database::close($lid);
    }

    #-------------------------------------------

    static function authentic($username, $password)
    {
        $username = addslashes($username);
        $password = LoginTable::encrypt($password);
        $password = addslashes($password);

$sql = <<< SQL
        SELECT password FROM login WHERE username = '$username';
SQL;

        $lid = Database::connect();
        $result = Database::query($sql, $lid);
        $row = mysql_fetch_row($result);
        Database::close($lid);
        return $row[0] == $password;        
    }

    #-------------------------------------------

    static function encrypt($plaintext)
    {
        $raw = crypt(md5($plaintext), md5($plaintext));
        return addslashes($raw);
    }
}

?>
