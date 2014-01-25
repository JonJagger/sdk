<?php
session_start();

require_once('common_banner.inc');
require_once('html_header.inc');
require_once('session.inc');
require_once('redirect.inc');
require_once('entry_table.inc');

#-----------------------------------------

$states;

class sax_handler
{
   function start_element($parser, $element, $attributes)
   {
       global $states;

       if ($element === 'entry')
       {
           $title = $attributes['title'];
           $status = $attributes['status'];
           if ($status == '')
           {
               $status = 'unspecified';
           }
           $states[$status][] = $title;
       }
   }
   
   function end_element($parser, $element)
   {
   }

}

function check($xml)
{
    $parser = xml_parser_create();
    $handler = new sax_handler();
    xml_set_object($parser, $handler);
    xml_set_element_handler($parser, 'start_element', 'end_element');
    xml_parser_set_option($parser, XML_OPTION_CASE_FOLDING, false);
    xml_parse($parser, $xml);
    xml_parser_free($parser);
}

function process()
{
    $titles = EntryTable::get_just_titles();
    sort($titles);

    foreach ($titles as $title_row)
    {
       $title = $title_row[0];
       $xml = EntryTable::get($title);
       check($xml);
    }
}

#-----------------------------------------

process();


$list = '<ul>';
foreach ($states as $status => $titles)
{
    $list .= '<li>';
    $list .= '<b>' . $status . '</b>';
    $list .= ' (' . count($titles) . ')';

    $list .= '<ul>';
    foreach ($titles as $title)
    {
        $list .= '<li>';
        $list .= "<a href='view.php?title=$title'>$title</a>";
        $list .= '</li>';
    }
    $list .= '</ul>';

    $list .= '</li>';
}
$list .= '</ul>';


$page = html_header('Status')
      . '<body>'
      . common_banner('')
      . $list
      . '</body></html>';


if (is_authenticated())
    echo $page;
else
    redirect("/login.php");

?>
