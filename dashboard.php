<?php
session_start();

require_once('entry_table.inc');
require_once('common_banner.inc');
require_once('word_count.inc');
require_once('html_header.inc');
require_once('session.inc');
require_once('redirect.inc');

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

$titles = EntryTable::get_all_titles();
foreach ($titles as $title_row)
{
    $title = $title_row[0];
    $entry_xml = $title_row[1];
    $wc = wordCount($entry_xml);
    $wc_total = $wc_total + $wc;
}
$entry_count = count($titles);
$average = (int) ($wc_total / $entry_count);
$info =  $entry_count . ' titles, ' . $wc_total . ' words, average=' . $average;

$page = html_header('Dashboard')
      . '<body>'
      . common_banner('')
      . $info
      . '</body></html>';


if (is_authenticated())
    echo $page;
else
    redirect("/login.php");

?>
