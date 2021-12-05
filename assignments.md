---
layout: page
title: Assignments
---

<style>
  .assignment {
    color: blue;
  }
  .due {
	color: red;
  }
  .class {
	color: green;
  }
  table.center {
    margin-left: auto;
	border: 1px solid black;
	margin-right: 1em;
	margin-bottom: 1em;
  }
  table.center th {
    background-color: black;
	color: white;
	text-align: center;
  }
  table.center td {
    padding: 3px;
  }
</style>

<table class="table table-hover">
	<tr>
		<th>
			Date Posted
		</th>
		<th>
			Date Due
		</th>
		<th>
			Assignment
		</th>
		<th>
			Turn-in Method
		</th>
	</tr>
	{% for info in site.data.assignments %}
	<tr>
	  <td>
	    {{ info.posted_date | newline_to_br }}
	  </td>
	  <td>
	    {{ info.due_date | newline_to_br }}
	  </td>
	  <td>
	    {{ info.assigned_work | newline_to_br }}
	  </td>
	  <td>
	    {{ info.turn_in_method | newline_to_br }}
	  </td>
	</tr>
	{% endfor %}
</table>
