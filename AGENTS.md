# Project Coding Guidance

When helping with C++ code in this project, consult and follow the common guidance from all three sources below. Apply the sources proportionately to this educational guidance-and-estimation simulator rather than claiming formal safety certification or full AUTOSAR compliance.

## Sources

1. [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
   - Use as the primary guide for modern C++ interfaces, type safety, ownership, resource management, functions, classes, and error handling.
2. [ROS 2 C++ Code Style and Language Versions](https://docs.ros.org/en/jazzy/The-ROS2-Project/Contributing/Code-Style-Language-Versions.html)
   - Use for robotics-oriented naming, formatting, file layout, and conventions where they do not conflict with this project's configured C++ version.
3. [AUTOSAR C++14 Guidelines for Critical and Safety-Related Systems](https://www.autosar.org/fileadmin/standards/R18-10-1/AP/AUTOSAR_RS_CPP14Guidelines.pdf)
   - Use relevant safety, predictability, initialization, type-conversion, control-flow, and defensive-programming guidance. Clearly distinguish following useful rules from verified AUTOSAR compliance.

## Application Rules

- Follow explicit user instructions and the project's configured C++ standard first.
- Prefer rules shared by the three sources.
- If the sources conflict, explain the conflict and recommend the rule most appropriate to this project before changing code.
- Explain standards-related recommendations in plain language while the user is learning C++.
- Do not introduce a newer C++ language version, external dependency, or strict safety restriction silently.
