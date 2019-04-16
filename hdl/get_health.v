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
    input wire [9:0] x1
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
    reg [31:0] heart_data;
    always @(posedge clk) begin
        if (animate) begin
            heart_data <= data;
        end
    end
endmodule
