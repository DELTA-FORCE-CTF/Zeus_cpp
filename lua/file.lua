-- Dump function
function dump(tbl, indent)
  if not indent then indent = 0 end
  for k, v in pairs(tbl) do
  	if type(k) == "number" then
  		k = "[" .. k .. "]"
  	end
  	local indentString = string.rep("  ", indent);
    local formatting = indentString .. k .. " = "
    if type(v) == "table" then
      print(formatting .. "{")
      dump(v, indent+1)
      print(indentString .. "}")
    elseif type(v) == 'boolean' then
      print(formatting .. tostring(v))      
    else
      print(formatting .. v)
    end
  end
end

--[[

**Mesh Creation**

The function zeus.register_blockmodel creates a blockmodel for use by blocks.
The first argument is the name of the model, which should be prefixed by the mod name and then a colon.
The next argument is a table of mesh parts. A mesh part is a table with mesh information in it.
The allowed information is as follows

face: which part of the block this mesh part is for, accepted strings are:
"top", "bottom", "left", "right", "front", "back", "nocull"

tex: The index of the textures array to use for texturing the mesh part

points: the points defining the mesh part. The format is defined by the mode property.

mode: Must be one of the following, default is "simple"

- simple:
The first five points are the top left vertice, the next five are the bottom right.

- vertex:
Define 5 positional coordinates for each face.

--]]

-- print(#zeus.registered_blockmodels);

-- Create cube model
zeus.register_blockmodel("default:block", {
    {
        face = "left",
        tex = 3,
        points = {
            0, 0, 0, 0, 1,
            0, 0, 1, 1, 1,
            0, 1, 1, 1, 0,
            0, 1, 0, 0, 0
        }
    }, {
        face = "right",
        tex = 4,
        points = {
            1, 1, 1, 1, 0,
            1, 0, 1, 1, 1,
            1, 0, 0, 0, 1,
            1, 1, 0, 0, 0
        }
    }, {
        face = "top",
        tex = 1,
        points = {
            0, 1, 0, 0, 0,
            0, 1, 1, 0, 1,
            1, 1, 1, 1, 1,
            1, 1, 0, 1, 0
        }
    }, {
        face = "bottom",
        tex = 2,
        points = {
            0, 0, 0, 0, 0,
            1, 0, 0, 1, 0,
            1, 0, 1, 1, 1,
            0, 0, 1, 0, 1
        }
    }, {
        face = "front",
        tex = 5,
        points = {
            0, 0, 1, 0, 1,
            1, 0, 1, 1, 1,
            1, 1, 1, 1, 0,
            0, 1, 1, 0, 0
        }
    }, {
        face = "back",
        tex = 6,
        points = {
            0, 0, 0, 0, 1,
            0, 1, 0, 0, 0,
            1, 1, 0, 1, 0,
            1, 0, 0, 1, 1
        }
    }
})

-- Create blockwithfoliage model
zeus.register_blockmodel("default:plantlike", {
    {
        face = "nocull",
        tex = 7,
        points = {
            0.15, 1, 0.15, 0, 1,
            0.85, 1, 0.85, 1, 1,
            0.85, 1.9, 0.85, 1, 0,
            0.15, 1.9, 0.15, 0, 0
        }
    }, {
        face = "nocull",
        tex = 7,
        points = {
            0.85, 1.9, 0.85, 1, 0,
            0.85, 1, 0.85, 1, 1,
            0.15, 1, 0.15, 0, 1,
            0.15, 1.9, 0.15, 0, 0
        }
    }, {
        face = "nocull",
        tex = 7,
        points = {
            0.85, 1.9, 0.15, 1, 0,
            0.85, 1, 0.15, 1, 1,
            0.15, 1, 0.85, 0, 1,
            0.15, 1.9, 0.85, 0, 0
        }
    }, {
        face = "nocull",
        tex = 7,
        points = {
            0.15, 1, 0.85, 0, 1,
            0.85, 1, 0.15, 1, 1,
            0.85, 1.9, 0.15, 1, 0,
            0.15, 1.9, 0.85, 0, 0
        }
    }
})

-- Create leaves model
zeus.register_blockmodel("default:block_poof", {
    {
        face = "left",
        tex = 0,
        points = {
            0, 0, 0, 0, 1,
            0, 0, 1, 1, 1,
            0, 1, 1, 1, 0,
            0, 1, 0, 0, 0
        }
    }, {
        face = "right",
        tex = 0,
        points = {
            1, 1, 1, 1, 0,
            1, 0, 1, 1, 1,
            1, 0, 0, 0, 1,
            1, 1, 0, 0, 0
        }
    }, {
        face = "top",
        tex = 0,
        points = {
            0, 1, 0, 0, 0,
            0, 1, 1, 0, 1,
            1, 1, 1, 1, 1,
            1, 1, 0, 1, 0
        }
    }, {
        face = "bottom",
        tex = 0,
        points = {
            0, 0, 0, 0, 0,
            1, 0, 0, 1, 0,
            1, 0, 1, 1, 1,
            0, 0, 1, 0, 1
        }
    }, {
        face = "front",
        tex = 0,
        points = {
            0, 0, 1, 0, 1,
            1, 0, 1, 1, 1,
            1, 1, 1, 1, 0,
            0, 1, 1, 0, 0
        }
    }, {
        face = "back",
        tex = 0,
        points = {
            0, 0, 0, 0, 1,
            0, 1, 0, 0, 0,
            1, 1, 0, 1, 0,
            1, 0, 0, 1, 1
        }
    }, {
        face = "nocull",
        tex = 0,
        points = {
            -0.31, 1.30, -0.3, 0, 0,
            -0.31, -0.30, -0.31, 0, 1,
            1.3, -0.30, 1.3, 1, 1,
            1.3, 1.30, 1.29, 1, 0,

            -0.31, 1.30, -0.3, 0, 0,
            -0.31, -0.30, -0.31, 0, 1,
            1.3, -0.30, 1.3, 1, 1,
            1.3, 1.30, 1.29, 1, 0,

            -0.31, 1.30, 1.29, 0, 0,
            -0.31, -0.30, 1.3, 0, 1,
            1.3, -0.30, -0.31, 1, 1,
            1.3, 1.30, -0.3, 1, 0,

            -0.31, 1.30, 1.29, 0, 0,
            -0.31, -0.30, 1.3, 0, 1,
            1.3, -0.30, -0.31, 1, 1,
            1.3, 1.30, -0.3, 1, 0
        }
    }
})

zeus.register_blockmodel("default:block_side_foliage", {
    {
        face = "left",
        tex = 3,
        points = {
            0, 0, 0, 0, 1,
            0, 0, 1, 1, 1,
            0, 1, 1, 1, 0,
            0, 1, 0, 0, 0
        }
    }, {
        face = "right",
        tex = 4,
        points = {
            1, 1, 1, 1, 0,
            1, 0, 1, 1, 1,
            1, 0, 0, 0, 1,
            1, 1, 0, 0, 0
        }
    }, {
        face = "top",
        tex = 1,
        points = {
            0, 1, 0, 0, 0,
            0, 1, 1, 0, 1,
            1, 1, 1, 1, 1,
            1, 1, 0, 1, 0
        }
    }, {
        face = "bottom",
        tex = 2,
        points = {
            0, 0, 0, 0, 0,
            1, 0, 0, 1, 0,
            1, 0, 1, 1, 1,
            0, 0, 1, 0, 1
        }
    }, {
        face = "front",
        tex = 5,
        points = {
            0, 0, 1, 0, 1,
            1, 0, 1, 1, 1,
            1, 1, 1, 1, 0,
            0, 1, 1, 0, 0
        }
    }, {
        face = "back",
        tex = 6,
        points = {
            0, 0, 0, 0, 1,
            0, 1, 0, 0, 0,
            1, 1, 0, 1, 0,
            1, 0, 0, 1, 1
        }
    }, {
        --Floats begin here
        face = "front",
        tex = 7,
        points = {
            0, 1, 1, 0, 0,
            0, 0.2, 1.2, 0, 1,
            1, 0.2, 1.2, 1, 1,
            1, 1, 1, 1, 0
        }
    }, {
        face = "back",
        tex = 7,
        points = {
            1, 0.2, -0.2, 1, 1,
            0, 0.2, -0.2, 0, 1,
            0, 1, 0, 0, 0,
            1, 1, 0, 1, 0
        }
    }, {
        face = "right",
        tex = 7,
        points = {
            1.2, 0.2, 1, 1, 1,
            1.2, 0.2, 0, 0, 1,
            1, 1, 0, 0, 0,
            1, 1, 1, 1, 0
        }
    }, {
        face = "left",
        tex = 7,
        points = {
            0, 1, 0, 0, 0,
            -0.2, 0.2, 0, 0, 1,
            -0.2, 0.2, 1, 1, 1,
            0, 1, 1, 1, 0
        }
    }
})

-- dump(zeus.registered_blockmodels["default:cube"]);

--[[

**Block Creation**

The function zeus.register_block creates a block in the game.
The first argument is the name of the block, which should be prefixed by the mod name and a colon.
The next argument is a table of properties. These are the following accepted properties:

name: The display name of the block

model: The blockModel of the block, will default to "default:cube"

textures: The list of textures for the blockmodel. Which textures go where are defined by the blockmodel.

--]]

-- Ignore this, it is temporary
-- Air
zeus.register_block("_:air", {
	name = "Air",
	model = "default:block",
	textures = {"_missing"}
})

-- Grass
zeus.register_block("default:grass", {
	name = "Grass",
	model = "default:block_side_foliage",
	textures = {
		"default_grass_top",
		"default_dirt",
        "default_grass_side",
        "default_grass_side",
        "default_grass_side",
        "default_grass_side",
        "default_grass_float",
	}
})

-- Dirt
zeus.register_block('default:dirt', {
	name = "Dirt",
	model = "default:block",
	textures = {"default_dirt"}
})

-- Stone
zeus.register_block('default:desert_cobblestone', {
	name = "Stone",
	model = "default:block",
	textures = {"default_stone_dark"}
})
