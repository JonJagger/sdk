
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

$misc = "<ul>";
$upper = "<ul>";
$lower = "<ul>";

foreach ($titles as $title_row)
{
   $title = $title_row[0];
   $link = '<li><a href="view.php?title=' . $title . '">' . $title . '</a></li>';
   if (strstr("ABCDEFGHIJKLMNOPQRSTUVWXYZ",$title[0]))
      $upper .= $link;
   else if (strstr("abcdefghijklmnopqrstuvwxyz",$title[0]))
      $lower .= $link;
   else
      $misc .= $link;
}
$misc .= "</ul>";
$upper .= "</ul>";
$lower .= "</ul>";

$page = html_header('A-Z')
      . "<body>"
      . common_banner('')
      . "<table><tr valign='top'>" 
      . "<td>" . $upper . "</td>"
      . "<td>" . $lower . "</td>"
      . "<td>" . $misc . "</td>"
      . "</tr></table>"
      . '</body></html>';

if (is_authenticated())
    echo $page;
else
    redirect("/login.php");

?>
