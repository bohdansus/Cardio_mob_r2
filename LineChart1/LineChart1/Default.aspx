<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="LineChart1._Default" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
     <title>PICST 2019</title>
 <meta charset="utf-8"></meta>
 <meta http-equiv="X-UA-Compatible" content="IE=edge"></meta>
 <meta name="viewport" content="width=device-width, initial-scale=1"></meta>
 <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
 <!-- http://t.co/dKP3o1e -->
 <meta name="HandheldFriendly" content="True"></meta>
 <meta name="MobileOptimized" content="320"></meta>
 <meta name="description" content="test"></meta>
 
 <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/2.1.4/jquery.min.js"></script>
 <script type="text/javascript" src="http://cdnjs.cloudflare.com/ajax/libs/jquery-csv/0.8.3/jquery.csv.min.js"></script>
 <script type="text/javascript" src="http://www.google.com/jsapi"></script>

<script type="text/javascript"> // load the visualisation API
  google.load('visualization', '1', { packages: ['corechart', 'controls'] });
</script>
<script type="text/javascript">
function drawVisualization() {
   $.get("AA.csv", function(csvString) {
      // transform the CSV string into a 2-dimensional array
      var arrayData = $.csv.toArrays(csvString, {onParseValue: $.csv.hooks.castToScalar});
      // this new DataTable object holds all the data
      var data = new google.visualization.arrayToDataTable(arrayData);
      var crt_ertdlyYY = new google.visualization.ChartWrapper({
         chartType: 'LineChart',
         containerId: 'crt_ertdlyYY',
         dataTable: data,
         options:{
            width: 650, height: 360,
            title: 'Heart Rate Signal received',
            titleTextStyle : {color: 'grey', fontSize: 11},
         }
      });
      crt_ertdlyYY.draw();
   });
}
google.setOnLoadCallback(drawVisualization)
</script>
</head>
<body>
    <form id="form1" runat="server">
      <div id="crt_ertdlyYY"></div>
    </form>
</body>
</html>
