const std = @import("std");
const lentity = @import("entity.zig");
const simengine = @import("main.zig");
const allocator = simengine.heap_allocator;
/// a
export const World = struct {
    entities: std.ArrayList(*lentity.Entity),

    /// **Creates** a new World. This could also be called a "scene".
    pub fn new() World {
        return World {
            .entities = std.ArrayList().init(allocator),
        };
    }
};
