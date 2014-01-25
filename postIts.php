<?php
session_start();

require_once('xslt_annotation.inc');
require_once('entry_table.inc');
require_once('common_banner.inc');
require_once('html_header.inc');
require_once('session.inc');
require_once('redirect.inc');

#-----------------------------------------

$titles = EntryTable::get_just_titles();
sort($titles);


foreach ($titles as $title_row)
{
   $title = $title_row[0];

   $xml_content = EntryTable::get($title);

   $post_its = xslt_post_its($xml_content, $title);
   if ($post_its != "")
   {
      $list .= $post_its;
   }
}


$page = html_header('Post-Its')
      . "<body>"
      . common_banner("")
      . $list
      . '</body></html>';


if (is_authenticated())
    echo $page;
else
    redirect("/login.php");

?>
