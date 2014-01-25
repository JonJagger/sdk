<?php
session_start();

require_once('xslt_annotation.inc');
require_once('common_banner.inc');
require_once('entry_table.inc');
require_once('html_header.inc');
require_once('make_edit_page.inc');
require_once('posted.inc');
require_once('redirect.inc');
require_once('session.inc');

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

function make_preview_form($title, $xml, $ts)
{
$escaped_xml = htmlspecialchars($xml);
$form = <<< FORM
<div class="preview-banner">PREVIEW</div>
<form action="edit.php?title=$title" method="POST">
  <input type="hidden" name="entry"   value="$escaped_xml"/>
  <input type="hidden" name="ts"      value="$ts"/>
  <input type="submit" name="re-edit" value="Re-Edit"/>
  <input type="submit" name="save"    value="Save"/>
   &nbsp;&nbsp;&nbsp;
  <input type="submit" name="cancel"  value="Cancel"/>
</form>
FORM;
return $form;
}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

function make_preview_page($title, $xml, $html, $ts)
{
    $head = html_header($title);
    $banner = common_banner("");
    $form = make_preview_form($title, $xml, $ts);

  $template = <<< TEMPLATE
  $head
  <body>    
    $banner
    $form
    <div class="preview-box">
     $html
    </div>
  </body>
</html>
TEMPLATE;
return $template;
}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

function preview_clicked($title)
{
    $xml = posted('entry');
    $ts = posted('ts');
    $html = @toHTML($xml);
    if ($html)
    {
        echo make_preview_page($title, $xml, $html, $ts);
    }
    else
    {
        echo make_edit_page4($title, " - Can't preview (Bad XML)", 
             $xml, $ts);
    }
}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

function reedit_clicked($title)
{
    $xml = posted('entry');
    $ts = posted('ts');
    echo make_edit_page4($title, "", $xml, $ts);
}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

function save_clicked($title)
{
    $xml = posted('entry');
    $ts = posted('ts');

    $html = @toHTML($xml);
    if ($html)
    {    
      $currentXml = EntryTable::get($title);
      if ($currentXml == "")
      {
          $result = EntryTable::insert($title, $xml); 
      }
      else
      {
          $result = EntryTable::change($title, $xml, $ts);
      }
      
      if ($result == 1)
          redirect("/view.php?title=$title");
      else
          echo make_edit_page4($title, " - Can't save (Concurrent update)",
              $xml, $ts);
    }
    else
    {
        echo make_edit_page4($title, " - Can't save (Bad XML)", 
             $xml, $ts);
    }

}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

function cancel_clicked($title)
{
    redirect("/view.php?title=$title");
}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

$title = $_GET['title'];
if ($title == "")
{
   # TODO: 
}

$method = $_SERVER['REQUEST_METHOD'];
if ($method == 'GET') 
{
    if (is_authenticated())
        echo make_edit_page($title);
    else
        redirect("/login.php?title=$title");
} 
else if ($method == 'POST') 
{
    if ($_POST['preview']) 
        preview_clicked($title);
    else if ($_POST['re-edit'])
        reedit_clicked($title);
    else if ($_POST['save']) 
        save_clicked($title);
    else if ($_POST['cancel'])
        cancel_clicked($title);
    else
        die('BUG: unexpected form submission');
} 
else 
{
    die('This script only works with GET and POST requests');
}

?>
