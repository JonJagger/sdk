<?php

# converts the xml content into html

function toHTML($xml)
{
$xsl = <<< XSL
<?xml version="1.0"?>
<xsl:stylesheet 
    version="1.0" 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
 <xsl:output method="xml" 
             encoding="utf-8" 
             omit-xml-declaration="yes" 
             cdata-section-elements="code"
             indent="no"/>

 <xsl:template match="/ | * | @*">
   <xsl:copy>
     <xsl:apply-templates select="* | @* | text()"/>
   </xsl:copy>
 </xsl:template> 

 <xsl:template match="/entry">
     <h2>
       <xsl:value-of select="@title"/>
     </h2>
     <xsl:apply-templates/>
 </xsl:template>

 <xsl:template match="//xref">
    <a>
      <xsl:attribute name="href">view.php?title=<xsl:value-of select="@title"/>
      </xsl:attribute>
      <xsl:choose>
         <xsl:when test=". = ''" >
            <xsl:value-of select="@title"/>      
         </xsl:when>
         <xsl:otherwise>
            <xsl:value-of select="."/>
         </xsl:otherwise>
      </xsl:choose>
    </a>
 </xsl:template>

 <xsl:template match="//quote">
    <div class="quote">
       <xsl:apply-templates/>
       <span>
         <xsl:attribute name="class">quote-info</xsl:attribute>            
           <xsl:value-of select="@author"/>
       </span>
    </div>
 </xsl:template>

 <xsl:template match="//code">
    <xsl:element name="pre">
       <xsl:attribute name="class">code</xsl:attribute>
       <xsl:value-of select="."/>
    </xsl:element>
 </xsl:template>

 <xsl:template match="//post-it">
    <div class="post-it">
       <span class="title">
          <xsl:value-of select="@title"/>
       </span>
       <xsl:apply-templates/>
    </div>
 </xsl:template>

</xsl:stylesheet>
XSL;

$xsltproc = new XsltProcessor();

$xslDom = DomDocument::loadXML($xsl);
$xsltproc->importStyleSheet($xslDom);
error_reporting(0); #Hack-City
$xmlDom = DomDocument::loadXML($xml);
error_reporting(1);

if ($xmlDom)
   $result = $xsltproc->transformToXML($xmlDom);
else
   $result = FALSE;

unset($xsltproc);

return $result;
}

#----------------------------------------------------

function xml_rename($xml, $new_title)
{
$xsl = <<< XSL
<?xml version="1.0"?>
<xsl:stylesheet 
    version="1.0" 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
 <xsl:output method="xml" 
             encoding="utf-8" 
             omit-xml-declaration="yes" 
             cdata-section-elements="code"
             indent="no"/>

 <xsl:template match="/ | * | @*">
   <xsl:copy>
     <xsl:apply-templates select="* | @* | text()"/>
   </xsl:copy>
 </xsl:template> 

 <xsl:template match="//entry">
   <entry title="$new_title">
     <xsl:apply-templates/>
   </entry>
 </xsl:template>

</xsl:stylesheet>
XSL;

$xsltproc = new XsltProcessor();
$xslDom = DomDocument::loadXML($xsl);
$xsltproc->importStyleSheet($xslDom);
$xmlDom = DomDocument::loadXML($xml);
$result = $xsltproc->transformToXML($xmlDom);
unset($xsltproc);

return $result;
}

#--------------------------------------------------------

function xslt_post_its($xml, $title)
{
$xsl = <<< XSL
<?xml version="1.0"?>
<xsl:stylesheet 
    version="1.0" 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
 <xsl:output method="xml" 
             encoding="utf-8" 
             omit-xml-declaration="yes" 
             cdata-section-elements="code"
             indent="no"/>

 <xsl:template match="/ | * | @*">
     <xsl:apply-templates select="* | @*"/>
 </xsl:template> 

 <xsl:template match="//post-it">
    <div class="post-it">
       <span class="heading">
          <xsl:value-of select="@title"/>
       </span>
       <xsl:value-of select="."/>
       <div>
       <xsl:text>[This post-it is in </xsl:text>
       <a href="/view.php?title=$title">$title</a>
       <xsl:text>]</xsl:text>      
       </div>
    </div>
 </xsl:template>

</xsl:stylesheet>
XSL;

$xsltproc = new XsltProcessor();
$xslDom = DomDocument::loadXML($xsl);
$xsltproc->importStyleSheet($xslDom);
error_reporting(0); #Hack-City
$xmlDom = DomDocument::loadXML($xml);
error_reporting(1);
$result = $xsltproc->transformToXML($xmlDom);
unset($xsltproc);

   return $result;
}


?>
