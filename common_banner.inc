<?php

require_once('session.inc');

$sdk = '<a href="home.php">' .
       'Software Development Knowledge (A to Z)' .
       '</a>';

function common_banner($title)
{
    global $sdk;

    if (is_authenticated())
    {
$lout = <<< HTML
    <span class="button">
    <form action="logout.php" method="POST">
       <input type="submit" name="logout" value="Logout"/>
    </form>
    </span>
HTML;

$banner = <<< BANNER
$lout
<h1>$sdk</h1>
<h2>
  <a href="table_of_contents.php#title=$title">A-Z</a>
  &nbsp;&nbsp;&nbsp;
  <a href="wordCount.php#title=$title">Word-Counts</a>
  &nbsp;&nbsp;&nbsp;
  <a href="recent.php">Most-Recent</a>
  &nbsp;&nbsp;&nbsp;
  <a href="onePage.php">All-Entries</a>
  &nbsp;&nbsp;&nbsp;
  <a href="postIts.php">All-Post-Its</a>
  <br/>
  $title
</h2>
BANNER;
return $banner;

    }
    else # must be in login page
    {
$banner = <<< BANNER
<h1>$sdk</h1>
<h2>
  $title
</h2>
BANNER;
    return $banner;
    }
}

?>
