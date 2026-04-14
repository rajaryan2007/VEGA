#pragma once
#include <yaml-cpp/yaml.h>
#include <glm/glm.hpp>

namespace YAML {

    template <> struct convert<glm::vec2> {
      static Node encode(const glm::vec2 &v) {
        Node node;
        node.push_back(v.x);
        node.push_back(v.y);
        return node;
      }
    
      static bool decode(const Node &node, glm::vec2 &v) {
        if (!node.IsSequence() || node.size() != 2)
          return false;
    
        v.x = node[0].as<float>();
        v.y = node[1].as<float>();
        return true;
      }
    };
    
    template <> struct convert<glm::vec3> {
      static Node encode(const glm::vec3 &v) {
        Node node;
        node.push_back(v.x);
        node.push_back(v.y);
        node.push_back(v.z);
        return node;
      }
    
      static bool decode(const Node &node, glm::vec3 &v) {
        if (!node.IsSequence() || node.size() != 3)
          return false;
    
        v.x = node[0].as<float>();
        v.y = node[1].as<float>();
        v.z = node[2].as<float>();
        return true;
      }
};

template <> struct convert<glm::vec4> {
  static Node encode(const glm::vec4 &v) {
    Node node;
    node.push_back(v.x);
    node.push_back(v.y);
    node.push_back(v.z);
    node.push_back(v.w);
    return node;
  }

  static bool decode(const Node &node, glm::vec4 &v) {
    if (!node.IsSequence() || node.size() != 4)
      return false;

    v.x = node[0].as<float>();
    v.y = node[1].as<float>();
    v.z = node[2].as<float>();
    v.w = node[3].as<float>();
    return true;
  }
};

inline YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec2 &v) {
  return out << YAML::Flow << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
}

inline YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec3 &v) {
  return out << YAML::Flow << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
}

inline YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec4 &v) {
  return out << YAML::Flow << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
}

} // namespace YAML