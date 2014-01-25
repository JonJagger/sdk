<?php

require_once('common_banner.inc');
require_once('entry_table.inc');
require_once('html_header.inc');
require_once('titles.inc');
require_once('xslt_annotation.inc');
require_once('word_count.inc');

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

function make_view_page($title)
{
    if (title_is_new($title))
    {
        title_create($title);
    }

    $head = html_header($title);
    $entry = EntryTable::get($title);
    $wc = wordCount($entry);
    if ($wc == 1) $plural = ''; else $plural = 's';
    $banner = common_banner(wordCount($entry) . ' word' . $plural);

    $html = toHTML($entry);

$template = <<< TEMPLATE
$head
<body ondblclick="document.location='http://54.246.47.161/edit.php?title=$title';">
  $banner
  <form action="view.php?title=$title" method="POST">
    <input type="submit" name="edit" value="Edit"/> (or double-click anywhere on the page)
    <div class="edit-box">
      $html
    </div>
  </form>
</body>
</html>
TEMPLATE;
return $template;
}

?>
