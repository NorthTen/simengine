const std = @import("std");
var heap_gpa = std.heap.GeneralPurposeAllocator(.{}){};
var heap_allocator = heap_gpa.allocator();


//export fn Deallocate() void {
//    heap_gpa.deinit();
//}
