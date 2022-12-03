//vec3 getRayFromScreenSpace(const vec2& pos)
//{
//    mat4 invMat = inverse(m_glData.getPerspective() * m_glData.getView());
//    vec4 near = vec4((pos.x - Constants::m_halfScreenWidth) / Constants::m_halfScreenWidth, -1 * (pos.y - Constants::m_halfScreenHeight) / Constants::m_halfScreenHeight, -1, 1.0);
//    vec4 far = vec4((pos.x - Constants::m_halfScreenWidth) / Constants::m_halfScreenWidth, -1 * (pos.y - Constants::m_halfScreenHeight) / Constants::m_halfScreenHeight, 1, 1.0);
//    vec4 nearResult = invMat * near;
//    vec4 farResult = invMat * far;
//    nearResult /= nearResult.w;
//    farResult /= farResult.w;
//    vec3 dir = vec3(farResult - nearResult);
//    return normalize(dir);
//}