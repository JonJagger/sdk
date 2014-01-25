<?php
session_start();

require_once('entry_table.inc');
require_once('common_banner.inc');
require_once('html_header.inc');
require_once('session.inc');
require_once('redirect.inc');

#-----------------------------------------

$titles = EntryTable::get_just_titles();
sort($titles);

$alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
for ($i = 0; $i < strlen($alphabet); $i++)
{
   $c = $alphabet[$i];
   $count[$c] = 0;
}

foreach ($titles as $title_row)
{
   $title = $title_row[0];
   $ic = $title[0]; #initial_character
   $count[$ic]++;
}

$list = "<ul>";
foreach ($titles as $title_row)
{
   $title = $title_row[0];
   $link = '<a href="view.php?title=' . $title . '">' . $title . '</a>';
   $list .= "<li>" . $link . "</li>";
}
$list .= "</ul>";

$page = html_header('A-Z')
      . "<body>"
      . common_banner('')
      . $list
      . '</body></html>';

if (is_authenticated())
    echo $page;
else
    redirect("/login.php");

?>
