Import("env")

project_src_dir = env["PROJECT_SRC_DIR"]

print(">> DEBUG: Source directory being used:", project_src_dir)

env.Append(
    LINKFLAGS=["-mfloat-abi=hard", "-mfpu=fpv4-sp-d16"],
    CCFLAGS=["-mfloat-abi=hard", "-mfpu=fpv4-sp-d16"],
    ASFLAGS=["-mfloat-abi=hard", "-mfpu=fpv4-sp-d16"],
)