module dividertb;

   reg [15:0] N;
   reg [15:0] D;
   reg 	      start;
   reg 	      clk;
   reg 	      reset;

   wire [7:0]  Q;
   wire [15:0] R;
   wire        done;

   divider mydiv(clk, reset, N, D, start, Q, R, done);
		 
   reg [15:0]  dvectors[19:0];
   reg [13:0]  vnum;
   initial
     begin
	$readmemh("divisor.tv", dvectors);
	vnum = 0;
     end
   
   initial
     begin
	clk = 0;
	start = 0;
	reset = 1;
     end

   always #25 clk = ~clk;
   
   initial 
     begin
	repeat (5) @(posedge clk) ;
	reset = 0;
	
	repeat (20)
	  begin
	     repeat (10) @(posedge clk) ;

	     N = 16'h1f40;
	     D = dvectors[vnum];
	     start = 1;
	     @(posedge clk) ;
	     start = 0;
	      
	     @(posedge done) ;
	     $display("%4h %4h %2h %4h\n", N, D, Q, R);
	     
	     vnum = vnum + 1;
	  end
	
	$finish;
	
     end
   
endmodule
