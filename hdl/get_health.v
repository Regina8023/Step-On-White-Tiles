///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: get_health.v
// File history:
//      <Revision number>: <Date>: <Comments>
//      <Revision number>: <Date>: <Comments>
//      <Revision number>: <Date>: <Comments>
//
// Description: 
//
// <Description here>
//
// Targeted device: <Family::SmartFusion> <Die::A2F200M3F> <Package::484 FBGA>
// Author: <Name>
//
/////////////////////////////////////////////////////////////////////////////////////////////////// 

//`timescale <time_units> / <precision>

module get_health( 
    input wire clk,
    input wire res,
    input wire write_en0,
    input wire right_addr,
    input wire [31:0] pwdata,
    input wire animate,
    input wire [9:0] x,
    input wire [8:0] y,
    output wire h,
    input wire [9:0] x0,
    input wire [8:0] y0
    );
    wire [31:0] data;
    get_data read_sq_info(
        .clk(clk),
        .res(res),
        .write_en0(write_en0),
        .right_addr(right_addr),
        .pwdata(pwdata),
        .data(data)
    );
    reg heart_data;
    always @(posedge clk) begin
        if (animate) begin
            heart_data <= data[0];
        end
    end
    assign s = 6;
    always @* begin
        if (x > x0 and )
    end
    assign l1 = ((y >= y0 & y < y0 + s & x > =x0 + s * 4 & x < x0 + s * 5));
    assign l2 = ((y >= y0 + s & y < y0 + s * 2 & x > =x0 + s * 3 & x < x0 + s * 6));
    assign l3 = ((y >= y0 + s * 2 & y < y0 + s * 3 & x > =x0 + s * 2 & x < x0 + s * 7));
    assign l4 = ((y >= y0 + s * 3 & y < y0 + s * 4 & x > =x0 + s * 1 & x < x0 + s * 8));
    assign l5 = ((y >= y0 + s * 4 & y < y0 + s * 5 & x > =x0 & x < x0 + s * 9));
    assign l6 = ((y >= y0 + s * 5 & y < y0 + s * 6 & ((x > =x0 & x < x0 + s * 4) | (x > =x0 + s * 5 & x < x0 + s * 9)));
    assign l7 = ((y >= y0 + s * 6 & y < y0 + s * 7 & ((x > =x0 + s & x < x0 + s * 3) | (x > =x0 + s * 6 & x < x0 + s * 8)));
    assign h = heart_data & (l1 | l2 | l3 | l4 | l5 | l6 | l7);
endmodule
