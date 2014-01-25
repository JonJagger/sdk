<?php 
session_start();

require_once('common_banner.inc');
require_once('html_header.inc');
require_once('posted.inc');
require_once('redirect.inc');
require_once('entry_table.inc');
require_once('session.inc');
require_once('login_table.inc');

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

function boxed($para)
{
    return '<div class="box">' . $para . '</div>';
}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

function select_titles($name)
{
    $titles = EntryTable::get_all_titles();
    sort($titles);

    $html = "<select name='$name'>";

    foreach ($titles as $title_row)
    {
       $title = $title_row[0];
       $html .= '<option>' . $title; # . '</option>';
    }
    $html .= '</select>';

    return $html;
}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

function pages()
{
$username = session_retrieve('username');
$delete_select = select_titles('deleteTitle');
$rename_select = select_titles('prevTitle');

$para = <<< PARA

<form action="home.php" method="POST">

<div class="box">
<h4>Titles</h4>
<div class="sep">
<input type="submit" name="newPage" value="Create"/>
a new entry whose title is:
<input type="text" name="newTitle"/>
</div>

<div class="sep">
<input type="submit" name="renamePage" value="Rename"/>
a entry's title from $rename_select
to 
<input type="text" name="nextTitle"/>
</div>

<div class="sep">
<input type="submit" name="deletePage" value="Delete"/>
the entry whose title is:
$delete_select
</option>
</div>
</div>

<div class="box">
<h4>Passwords</h4>
<div class="sep">
<input type="submit" name="changePassword" value="Change"/>
$username's password to
<input type="password" name="newPassword" value=""/>
confirmed as
<input type="password" name="confirmedAs" value=""/>
</div>
</div>


<div class="box">
<h4>Misc</h4>
<ul>
<li>
The SDK A-Z hyperlink at the top left always brings you back to this page.
</li>
<li>
Saves/renames are handled using optimistic locking. 
If a save/rename fails it is because of a concurrent save/rename.
</li>
<li>
This wiki runs on PHP5+ and MySQL5+ and uses the libxml2.8.0
and libxsl1.1.26 extensions.
</li>
</ul>
</div>
</form>

PARA;
return $para;
}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

function make_home_page()
{
$page = html_header('Home')
      . '<body>'
      . common_banner('Home Page')
      . pages() 
      . '</body></html>';

return $page;
}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

$method = $_SERVER['REQUEST_METHOD'];
if ($method == 'GET') 
{
    if (is_authenticated())
        echo make_home_page();
    else
        redirect("/login.php");
}
else if ($method == 'POST') 
{
    if ($_POST['newPage'])
    {
        $title = posted('newTitle');
        if ($title != "")
        {
            redirect("/edit.php?title=$title");
        }
        else
        {
            redirect("/home.php");
        }
    }
    else if ($_POST['renamePage'])
    {
        $title = posted('prevTitle');
        $newTitle = posted('nextTitle');
        if ($title != "" and $newTitle != "")
        {
            EntryTable::rename($title, $newTitle);
        }
        redirect("/home.php");
    }
    else if ($_POST['deletePage'])
    {
        $title = posted('deleteTitle');
        if ($title != "")
        {
            EntryTable::remove($title);
        }
        redirect("/home.php");
    }
    else if ($_POST['changePassword'])
    {
        $username = session_retrieve('username');
        $newPassword = posted('newPassword');
        $confirmedAs = posted('confirmedAs');
        if ($newPassword != "" and $newPassword == $confirmedAs)
        {
            LoginTable::change_password($username, $newPassword);
            redirect("/home.php");
        }
        else
            redirect("/home.php?passWordChanged=no(entries unequal)");
        
    }
    else
        die('BUG: unexpected form POST submission');
} 
else 
{
    die('This script only works with GET and POST requests');
}

?>
