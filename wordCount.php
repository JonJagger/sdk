<?php
session_start();

require_once('entry_table.inc');
require_once('common_banner.inc');
require_once('word_count.inc');
require_once('html_header.inc');
require_once('session.inc');
require_once('redirect.inc');

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

$sorted = Array();
$titles = EntryTable::get_all_titles();
$count = 0;
foreach ($titles as $title_row)
{
    $title = $title_row[0];
    $entry_xml = $title_row[1];
    $wc = wordCount($entry_xml);
    $sorted[$wc][] = $title;
    $wc_total = $wc_total + $wc;
    $count++;
}
ksort($sorted);

$stats = '';
$stats .= '<h3>number of entries = ' . $count . '<br/>';
$stats .= 'total number of words = ' . $wc_total . '<br/>';
$stats .= 'average words/entry = ' . (int)($wc_total / $count);
$stats .= '</h3>';

$list = '<ul>';
foreach ($sorted as $wc => $titles)
{
    foreach ($titles as $index => $title)
    {
      $link = '<a href="view.php?title=' . $title . '">' . $title . '</a>';
      $list .= '<li>' . $wc . ' ' . $link . '</li>';
    }
}
$list .= '</ul>';

$page = html_header('Word Count')
      . '<body>'
      . common_banner($stats)
      . $list
      . '</body></html>';


if (is_authenticated())
    echo $page;
else
    redirect("/login.php");

?>
