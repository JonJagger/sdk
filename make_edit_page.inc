<?php

require_once('entry_table.inc');
require_once('html_header.inc');
require_once('common_banner.inc');

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

function instructions()
{
$info = <<< INFO
<a name="XML"></a>
<div class="box">
<h2>XML</h2>
The entry for each title must take the form:
<pre style="background-color: white;">
&lt;entry title="TITLE" status="STATUS"&gt;
...
&lt;/entry&gt;
</pre>
<ul>
<li>&lt;entry&gt; must be well-formed XML</li>
<li>The title attribute is required.</li>
<li>The status attribute is optional and defaults to
unspecified.</li>
 <li>
Write <code style="background-color: white;">&amp;amp;</code>
to get a <code style="background-color: white;">&amp;</code> 
</li>
 <li>
Write <code style="background-color: white;">&amp;lt;</code>
to get a <code style="background-color: white;">&lt;</code> 
</li>
</ul>
</div>

<div class="box">
<a name="CrossReferences"></a>
<h2>Cross References</h2>
There are two ways to use the &lt;xref&gt; tag to
add a cross-reference hyperlink to an existing title.
<ul>
<li>
The link text defaults to the same as the title attribute.
</br>
For example the following hyperlinks to the Abstraction title
 - like this <a href="view.php?title=Abstraction">Abstraction</a>
<pre style="background-color: white;">
&lt;xref title="Abstraction"/&gt;
</pre>
</li>
<li>
The link text is explicitly provided by the &lt;xref&gt; text.
</br>
For example the following also hyperlinks to the Abstraction title
 - like this <a href="view.php?title=Abstraction">Selective Ignorance</a>
<pre style="background-color: white;">
&lt;xref title="Abstraction"&gt;Selective Ignorance&lt;/xref&gt;
</pre>
</li>
</ul>
</div>

<div class="box">
<a name="CodeFragments"></a>
<h2>Code Fragments</h2>
Here's how to add a code fragment:
<pre style="background-color: white;">
&lt;code&gt;&lt;![CDATA[
...
]]&gt;&lt;/code&gt;
</pre>
For example, this...
<pre style="background-color: white;">
&lt;code&gt;&lt;![CDATA[
class weleaser
{
public:
    void welease(const std::string &amp; name)
    {
        if (name == "Bwian")
        {
            ...
        }
    }
};
]]&gt;&lt;/code&gt;
</pre>
...becomes this...
<pre class="code">
class weleaser
{
public:
    void welease(const std::string & name)
    {
        if (name == "Bwian")
        {
            ...
        }
    }
};
</pre>
</div>

<div class="box">
<a name="Quotes"></a>
<h2>Quotes</h2>
Here's how to add a quote:
<pre style="background-color: white;">
&lt;quote author="WHO"&gt;
...
&lt;/quote&gt;
</pre>
<ul>
<li>&lt;quote&gt; must be well-formed XML</li>
<li>The author attribute is optional and has no default.</li>
</ul>
For example, this...

<pre style="background-color: white;">
&lt;quote author="Douglas Adams"&gt;
You're really not going to like it.
&lt;/quote&gt;
</pre>

...becomes this...

<div class="quote">
You're really not going to like it.
<span class="quote-info">
Douglas Adams
</span>
</div>
</div>

<div class="box">
<a name="PostIts"></a>
<h2>Post-Its</h2>

Here's how to add a post-it note:
<pre style="background-color: white;">
&lt;post-it title="WHAT"&gt;
...
&lt;/post-it&gt;
</pre>
<ul>
<li>&lt;post-it&gt; must be well-formed XML</li>
<li>The title attribute is optional and has no default.</li>
</ul>
For example...

<span class="post-it">
<h4>Plumber</h4>
Thursday 3:00pm
</span>

<pre style="background-color: white;">
&lt;post-it title="Plumber"&gt;
Thursday 3:00pm.
&lt;/post-it&gt;
</pre>
You can use &lt;xref&gt;, &lt;code&gt;, or &lt;quote&gt; 
tags inside a post-it.
</div>

INFO;
return $info;
}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

function make_edit_page($title)
{
    $entry = EntryTable::get($title);
    # if brand new entry add outer xml tags and save in database
    if ($entry == "")
    {
        $entry = '<entry title="' 
                . $title 
                . '">'
                . "\r\n"
                . '<p>' 
                . "\r\n\r\n"
                . '</p>'
                . "\r\n"
                . '</entry>';

        #EntryTable::insert($title, $entry);
    }
    $ts = EntryTable::get_ts($title);

    # until time to save again make html friendly
    #$entry = htmlspecialchars($entry);

    return make_edit_page4($title, "", $entry, $ts);
}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

function make_edit_page4($title, $suffix, $entry, $ts)
{
$head = html_header($title);
$banner = common_banner($title . "  " . $suffix);
$info = instructions();

$entry = htmlspecialchars($entry);

$page = <<< PAGE
$head
<body>
$banner
<div class="box">
<form action="edit.php?title=$title" method="POST">
  <input type="hidden" name="ts"   value="$ts"/>
  <input type="submit" name="preview" value="Preview"/>
  <input type="submit" name="save"    value="Save"/>
   &nbsp;&nbsp;&nbsp;
  <input type="submit" name="cancel"  value="Cancel"/>
  (see below for information on
  <a href="#XML">XML</a> 
  <a href="#CrossReferences">Cross-References</a>
  <a href="#CodeFragments">Code-Fragments</a>
  <a href="#Quotes">Quotes</a>
  <a href="#PostIts">Post-Its</a>)
  
  <br/>
  <textarea cols="100" rows="30" name="entry">$entry</textarea>
  <br/>
  <input type="submit" name="preview" value="Preview"/>
  <input type="submit" name="save"    value="Save"/>
   &nbsp;&nbsp;&nbsp;
  <input type="submit" name="cancel"  value="Cancel"/>
  <br/>
</form>
</div>
$info
</body>
</html>
PAGE;

return $page;
}

?>
