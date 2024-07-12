import plotly.graph_objects as go

# Reading the open and readlink data
with open("./open_nanoseconds.txt", "r") as open_file:
    open_data = [int(line.strip()) for line in open_file]

with open("./readlink_nanoseconds.txt", "r") as readlink_file:
    readlink_data = [int(line.strip()) for line in readlink_file]

# Create x-axis values to represent the nth iteration
x = list(range(1, len(open_data) + 1))



difference = [readlink_data[i] - open_data[i] for i in range(len(open_data))]

# Create a figure
fig = go.Figure()


formatted_customdata = [list(tup) for tup in zip(readlink_data, difference)]

fig.add_trace(
    go.Scatter(
        x=x,
        y=open_data,
        mode="lines",
        name="open",
        hovertemplate="Iteration: %{x}<br>open: %{y} nanoseconds<br>readlink: %{customdata[0]} nanoseconds<br>difference: %{customdata[1]} nanoseconds",
        customdata=formatted_customdata,
    )
)


formatted_customdata = [list(tup) for tup in zip(open_data, difference)]

fig.add_trace(
    go.Scatter(
        x=x,
        y=readlink_data,
        mode="lines",
        name="readlink",
        hovertemplate="Iteration: %{x}<br>readlink: %{y} nanoseconds<br>open: %{customdata[0]} nanoseconds<br>difference: %{customdata[1]} nanoseconds",
        customdata=formatted_customdata,
    )
)

fig.add_annotation(
    x=0.5, 
    y=-0.15, 
    xref="paper", 
    yref="paper",
    showarrow=False, 
    text="This graph compares the performance of 'open' and 'readlink' operations."
    + "\n\n'open' data represents the time taken to open files, "
    + "'readlink' data shows the time to read symbolic links, "
    + "and 'difference' indicates the time difference between these operations; "'readlink time - open time'".",
    align="left",  
    font=dict(size=12),
)


fig.update_layout(
    xaxis_title="Line number",
    yaxis_title="Time (nanoseconds)",
    title="Comparison of open and readlink",

    margin=dict(b=100)
)


fig.show()
