<?php
session_start();

require_once('entry_table.inc');
require_once('common_banner.inc');
require_once('html_header.inc');
require_once('session.inc');
require_once('redirect.inc');

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

$sorted = Array();
$titles = EntryTable::get_all_titles();
foreach ($titles as $title_row)
{
    $title = $title_row[0];
    $ts = $title_row[2];

    $sorted[$ts][] = $title;
}
ksort($sorted);
$sorted = array_reverse($sorted);

$list = '<ul>';
foreach ($sorted as $ts => $titles)
{
    foreach ($titles as $title)
    {
      $link = '<a href="view.php?title=' . $title . '">' . $title . '</a>';
      $list .= '<li>' . $ts . ' ' . $link . '</li>';
    }
}
$list .= '</ul>';

$page = html_header('Recent')
      . '<body>'
      . common_banner('')
      . $list
      . '</body></html>';


if (is_authenticated())
    echo $page;
else
    redirect("/login.php");

?>
