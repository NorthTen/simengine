const std = @import("std");
const lworld = @import("world.zig");
const simengine = @import("main.zig");
const allocator = simengine.heap_allocator;

/// A being, or an object, or something.
export const Entity = struct {
    id:comptime_int,
    components:std.ArrayList(struct {}),

    /// **Creates** a new Entity.
    /// **Make sure you have a World created first before creating any entities.**
    pub fn new(world: *lworld.World) Entity {
        return Entity {
            .id = world.entities.items.len,
            .components = std.ArrayList().init(allocator)
        };
    }

    /// Adds a new component to the Entity.
    pub fn addComponent(self: *Entity, component: anyopaque) void {
        self.components.addOne(component);
    }
};
