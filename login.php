<?php
session_start();

require_once('common_banner.inc');
require_once('html_header.inc');
require_once('posted.inc');
require_once('redirect.inc');
require_once('session.inc');
require_once('login_table.inc');

#-------------------------------------

function make_login_form($username)
{
    $form = <<< FORM
<div class="box">
  <form action="$_PHP_SELF" method="POST">
    <table>
       <tr>
          <td>Username</td>
          <td><input type="text" name="username" value="$username"/></td>
       </tr>
       <tr>
          <td>Password</td>
          <td><input type="password" name="password" value=""/></td>
       </tr>
    </table>
    <input type="submit" name="login" value="Login"/>
  </form>
</div>
FORM;

    return $form;
}

#-------------------------------------

function make_login_page($username, $suffix)
{
    if ($suffix) 
        $suffix = " - " . $suffix;

$page = html_header('Login')
      . '<body>'
      . common_banner('Login' . $suffix)
      . make_login_form($username)
      . '</body></html>';

return $page;    
}

#-------------------------------------

function enter()
{
    redirect("/recent.php");
}

#-------------------------------------

$method = $_SERVER['REQUEST_METHOD'];

if ($method == 'GET') 
{
    if (is_authenticated())
    {
        enter();
    }
    else
    {
       $username = session_retrieve('username');
       echo make_login_page($username, "");
    }
}
else if ($method == 'POST') 
{
    $username = posted('username');
    session_remember('username', $username);
    $password = posted('password');
    $valid = LoginTable::authentic($username, $password);
    $password = "";

    if ($valid)
    {
        session_remember('auth', true);
        enter();
    }
    else
    {
        if (isset($title))
            echo make_login_page($username, "failed");
        else
            echo make_login_page($username, "failed");
    }
}
else
{
    die("This script only works with GET and POST requests");
}

?>
