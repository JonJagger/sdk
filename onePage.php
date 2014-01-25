<?php
session_start();

require_once('entry_table.inc');
require_once('common_banner.inc');
require_once('html_header.inc');
require_once('xslt_annotation.inc');
require_once('redirect.inc');
require_once('session.inc');

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

function make_one_page()
{
    $head = html_header('Everything');
    $banner = common_banner('');

    $titles = EntryTable::get_all_titles();
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
        if ($ic != $previous)
        {
           $page .= '<a name="' . $ic . '"></a>';
        }
        $previous = $ic;

        $title = ereg_replace(' ', 'XXX', $title);
        $xml = $title_row[1];
        $html = toHTML($xml);
        $page .= '<div class="box">'
              . "<input type='submit' name='$title' value='Edit'/>"
              .  $html 
              . '</div>';
    }

    foreach ($count as $key => $value)
    {
       if ($value != 0)
           $az .= ' <a href="#' . $key . '">' . $key . '</a>';
       else
           $az .= ' ' . $key;
    }

$template = <<< TEMPLATE
$head
<body>
  $banner
  $az
  <form action="onePage.php" method="POST">
    $page
  </form>
</body>
</html>
TEMPLATE;
return $template;

}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

$method = $_SERVER['REQUEST_METHOD'];
if ($method == 'GET') 
{
    if (is_authenticated())
        echo make_one_page();
    else
        redirect("/login.php?title=$title");
}
else if ($method == 'POST')
{
    $titles = EntryTable::get_all_titles();
    foreach ($titles as $title_row)
    {
        $title = $title_row[0];
        $stitle = ereg_replace(' ', 'XXX', $title);
        if ($_POST[$stitle])
        {
            redirect("/edit.php?title=$title");
        }
    }    
}
else
{
    die('This script only works with GET or POST requests');
}

?>
